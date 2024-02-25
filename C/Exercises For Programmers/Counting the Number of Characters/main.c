#include <stdio.h>
#include <stdlib.h>
#include "main.h"

enum { kBufferLen = 64 };

int main(int argc, char *argv[]){
    printf("Enter an input string: ");
    char in_buffer[kBufferLen] = { 0 };
    if(safe_gets(in_buffer, kBufferLen, stdin) == NULL){
        printf("safe_gets returned NULL.");
        return EXIT_FAILURE;
    }
    int len = get_length_recursive_ternary(in_buffer, 0);
    printf("[ %s ] has %d characters.", in_buffer, len);
    return EXIT_SUCCESS;
}

int get_length(char *buf){
    int len = 0;
    while(*buf != '\0'){
        len++;
        buf++;
    }
    return len;
}

int get_length_recursive(char *buf, int len){
    if(*buf == '\0'){
        return len;
    } else {
        return get_length_recursive(++buf, ++len);
    }
}

int get_length_recursive_ternary(char *buf, int len){
    return *buf == '\0' ? len : get_length_recursive_ternary(++buf, ++len);
}

char *safe_gets(char *buf, int size, FILE *stream){
    if( fgets(buf, size, stream) ){
        for(int i = 0; i < size; i++){
            if(buf[i] == '\n'){
                buf[i] = '\0';
                break;
            }
        }
        return buf;
    } else {
        return NULL;
    }
}