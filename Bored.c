#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include <netdb.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

#define PORT "80"
#define MAXDATASIZE 128
#define NUM_IPv4_ADDRESSES "4294967296"


void sip_to_iip(char *ip, int *iip);
void print_ip(int *iip, int num_octets);
void iip_to_sip(int *iip, int num_octets, char buf[128]);
void increment_ip(int *iip, int num_octets);
int grab_banner(char host[128]);

int main(int argc, char **argv){
    int int_ip[4];
    
    if(argc < 2 || argc > 3){
        printf("\nusage: %s <starting_ip_address> <range>\n\n", argv[0]);
        exit(1);
    }
    if(argv[2] == NULL){
        argv[2] = NUM_IPv4_ADDRESSES;
    }

    sip_to_iip(argv[1], int_ip);
    char sip[128] = {'\0'};
    for(long i = 0; i < atol(argv[2]); i++){
        iip_to_sip(int_ip, sizeof(int_ip)/sizeof(int_ip[0]), sip);
        printf("[+] Address: %s\n", sip);
        increment_ip(int_ip, sizeof(int_ip)/sizeof(int_ip[0]));
        grab_banner(sip);
        memset(sip, 0, 128);
        sleep(2);
    }
}

int grab_banner(char host[128]){
    /* getaddrinfo */
    int rv, sockfd, numbytes;
    char buf[MAXDATASIZE];
    struct addrinfo hints, *res;
    
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    if(getaddrinfo(host, PORT, &hints, &res) != 0){
        printf("[-] grab_banner getaddrinfo\n");
        return -1;
    }
    /*printf("[+] grab_banner getaddrinfo\n");*/

    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if(sockfd == -1){
        printf("[-] grab_banner socket\n");
        return -1;
    }
    /*printf("[+] grab_banner socket\n");*/

    if(connect(sockfd, res->ai_addr, res->ai_addrlen) != 0){
        printf("[-] grab_banner connect\n"); 
        return -1;
    }
    /*printf("[+] grab_banner connect\n");*/

    char *msg = "GET / HTTP/1.0\r\n\r\n";
    numbytes = send(sockfd, msg, strlen(msg), 0);
    if(numbytes == -1){
        printf("[-] grab_banner send\n");
        return -1;
    }
   /* printf("[+] grab_banner send: %d\n", numbytes);*/

    numbytes = recv(sockfd, buf, MAXDATASIZE-1, 0);
    if(numbytes == -1){
        printf("[-] grab_banner recv\n");
    }
    printf("[+] grab_banner recv: %d\n", numbytes);

    buf[numbytes] = '\0';
    printf("%s\n", buf);
    close(sockfd);
    memset(buf, 0, MAXDATASIZE);
}

void iip_to_sip(int *iip, int num_octets, char buf[128]){
    char octet_buf[32] = {'\0'};
    for(int i = 0; i < num_octets; i++){
        if(i == 3){
            sprintf(octet_buf, "%d", iip[i]);
        }else{
            sprintf(octet_buf, "%d.", iip[i]);
        }
        strcat(buf, octet_buf);
        memset(octet_buf, 0, sizeof(octet_buf));
    }
    /*printf("[+] iip_to_sip buf: %s\n", buf);*/
}

void increment_ip(int *iip, int num_octets){
    for(int i = num_octets-1; i >= 0; i--){
        if(iip[i] == 255){
            iip[i] = 0;
        }else{
            iip[i] = iip[i] + 1;
            break;
        }
    }
}

void print_ip(int *iip, int num_octets){
    for(int i = 0; i < num_octets; i++){
        printf("%d", iip[i]);
        if(i < num_octets - 1){
            printf(".");
        }else{
            printf("\n");
        }
    }
}

void sip_to_iip(char *ip,int *iip){
    char octet[4] = {'\0'};
    char *o = octet;
    
    for(int i = 0; i < 4; i++){
        while(*ip != '.' && *ip != '\0'){
            *o = *ip; 
            o++;
            ip++;
        }
        /*printf("[+] sip_to_iip octet: %s\n", octet);*/
        iip[i] = atoi(octet);
        o = octet;
        ip++;
        memset(octet, 0, sizeof(octet));
    }
}
