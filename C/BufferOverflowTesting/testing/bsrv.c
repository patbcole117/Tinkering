#include <sys/types.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
    struct addrinfo addr_hints;
    struct addrinfo *addr_res;
    struct sockaddr_storage client_addr;
    int srv_sockfd, client_sockfd, recv_val;
    int sockoptval=1;
    char recv_buffer[256];

    if(argc != 2){
        printf("Usage: %s PORT\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    memset(&addr_hints, 0, sizeof(addr_hints));
    addr_hints.ai_family = AF_INET;
    addr_hints.ai_socktype = SOCK_STREAM;
    addr_hints.ai_flags = AI_PASSIVE;
    if((getaddrinfo(NULL, argv[1], &addr_hints, &addr_res)) !=0){
        perror("getaddrinfo");
        exit(EXIT_FAILURE);
    }
    /* Now addr_res should hold a pointer to a linked list of results. */

    srv_sockfd = socket(addr_res->ai_family, addr_res->ai_socktype,
                    addr_res->ai_protocol);
    if(srv_sockfd < 0){
        perror("socket");
        exit(EXIT_FAILURE);
    }
    /* Now there is a socket with a file descriptor for send/recv. */
    
    if((bind(srv_sockfd, addr_res->ai_addr, addr_res->ai_addrlen)) <0){
        perror("bind");
        exit(EXIT_FAILURE);
    }
    if((setsockopt(srv_sockfd, SOL_SOCKET, SO_REUSEADDR, &sockoptval,
        sizeof(int))) !=0){
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    /* Now the socket is bound to the compuer and will reuse ports. */    

    if((listen(srv_sockfd, 5)) !=0){
        perror("listen");
        exit(EXIT_FAILURE);
    }
    /* Now the socket is listening for connections. */

    int client_addr_size = sizeof(client_addr);
    client_sockfd = accept(srv_sockfd, (struct sockaddr *)&client_addr,
                           &client_addr_size);
    if(client_sockfd < 0){
        perror("accept");
        exit(EXIT_FAILURE);
    }
    /* Now the server is ready to recv data. */
    
    memset(recv_buffer, 0, 256);
    recv_val = recv(client_sockfd, recv_buffer, 255, 0);

    if(recv_val > 0){
        printf("Received %d bytes.\n", recv_val);
        printf("Message: %s\n", recv_buffer);
      
    }else if(recv_val == 0){
        printf("Client closed connection.\n");
    }else{
        perror("recv");
        exit(EXIT_FAILURE);
    }

    return 0;
}

