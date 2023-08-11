#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <poll.h>



int get_disp_sock(char *port){
    int disp_sock;
    int soptval = 1;

    struct addrinfo hints, *res;

    /* addrinfo */
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    if((getaddrinfo(NULL, port, &hints, &res)) != 0){
        perror("getaddrinfo");
        exit(EXIT_FAILURE);
    }

    /* socket */
    disp_sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if(disp_sock < 0){
        perror("socket");
        exit(EXIT_FAILURE);
    }

    /* setsockopt */
    if((setsockopt(disp_sock, SOL_SOCKET, SO_REUSEADDR,
                    &soptval, sizeof(int)) != 0)){
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    /* bind */
    if(bind(disp_sock, res->ai_addr, res->ai_addrlen) != 0){
        perror("bind");
        exit(EXIT_FAILURE);
    }

    /* listen */
    if(listen(disp_sock, 5) != 0){
        perror("listen");
        exit(EXIT_FAILURE);

    }

    freeaddrinfo(res);
    return disp_sock;
}


int add_pfds(struct pollfd *pfds[], int new_fd, int *pfds_num, int *pfds_max){
        
        if(*pfds_num == *pfds_max){
            *pfds_max *= 2;

            *pfds = realloc(*pfds, sizeof(**pfds) * (*pfds_max));
        }

        (*pfds)[*pfds_num].fd = new_fd;
        (*pfds)[*pfds_num].events = POLLIN;
        (*pfds_num)++;
}


int remove_pfds(struct pollfd pfds[], int i, int *pfds_num){
    pfds[i] = pfds[*pfds_num-1];
    (*pfds_num)--;
}


int handle_message(char *recv_buff, int sock_fd){
    memset(recv_buff, 0, 256);
    int recv_len = recv(sock_fd, recv_buff, 256-1, 0);

    if((recv_len > 0)){
        printf("%d: %s\n", sock_fd, recv_buff);
        return 0;
    }
    if((recv_len == 0)){
        printf("srv: %d CLOSED!\n\n", sock_fd);
    }else{
        perror("recv");
        exit(EXIT_FAILURE);
    }

    close(sock_fd);
    return -1;
}


int main(int argc, char *argv[]){
    int disp_fd, new_fd, pfds_num;
    int pfds_max = 5;
    char recv_buff[256];
    socklen_t addrlen;
    struct sockaddr_storage addr_sto;
    struct pollfd *pfds = malloc(sizeof(*pfds) * pfds_max);

    /* verify args */ 
    if(argc != 2){
        printf("usage: %s port\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    /* get dispatcher socket */
    disp_fd = get_disp_sock(argv[1]);
    if(disp_fd < 0){
        perror("get_disp_sock");
        exit(EXIT_FAILURE);
    }

    pfds[0].fd = disp_fd;
    pfds[0].events = POLLIN;
    pfds_num++;

    for(;;){
        int poll_count = poll(pfds, pfds_max, -1);
        if(poll_count < 0){
            perror("poll");
            exit(EXIT_FAILURE);
        }

        for(int i = 0; i < pfds_num; i++){
            if(pfds[i].revents & POLLIN){
                if(pfds[i].fd == disp_fd){
                    /* If the poll is a new connection. */
                    addrlen = sizeof(addr_sto);
                    new_fd = accept(disp_fd, (struct sockaddr *)&addr_sto,
                                    &addrlen);
                    if(new_fd < 0){
                        perror("new_fd accept");
                        exit(EXIT_FAILURE);
                    }else{
                        add_pfds(&pfds, new_fd, &pfds_num, &pfds_max);
                        printf("srv: %d CONNECTED!\n\n", new_fd);
                    }

                }else{
                    /* If the poll is an existing conection. */
                    if((handle_message(recv_buff, pfds[i].fd)) < 0){
                        remove_pfds(pfds, i, &pfds_num);
                    }
                }
            }
        }
    }
    return 0;
}
