#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main(int argc, char *argv[]){
    int socket_fd, client_socket, length_of_addr, status;
    char storage_buffer[256];
    int option_value = 1;
    struct sockaddr_in server_addr, connection_addr;
    char *message = "This is a message from the server.";

    if(argc != 3){
        printf("usage: %s IP PORT\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(socket_fd < 0){
        perror("Socket creation failed.");
        exit(EXIT_FAILURE);
    }

    status = setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &option_value,
                        sizeof(option_value));
    if(status < 0){
        perror("Unable to setsockopt().");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_zero[8]='\0';
    status=bind(socket_fd, (struct sockaddr*)&server_addr,
                sizeof(struct sockaddr));
    if(status < 0){
       perror("Could not bind socket.");
       exit(EXIT_FAILURE);
    }

    status=listen(socket_fd, 4);
    if(status<0){
        perror("Listening failed.");
        exit(EXIT_FAILURE);
    }
    
    length_of_addr = sizeof(connection_addr);
    client_socket = accept(socket_fd, (struct sockaddr*)&connection_addr,
                           &length_of_addr);
    if(client_socket<0){
        perror("Could not accept connection.");
        exit(EXIT_FAILURE);
    }
    
    memset(storage_buffer, 0, 256);
    read(client_socket, storage_buffer, 255);
    printf("Message received: %s\n", storage_buffer);
    
    send(client_socket, message, strlen(message), 0);
    close(socket_fd);
    close(client_socket);
    exit(EXIT_SUCCESS);
}
