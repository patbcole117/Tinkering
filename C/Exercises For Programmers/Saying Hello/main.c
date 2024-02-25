#include <stdio.h>
#include <stdlib.h>
#include "main.h"

enum { kBufferSize = 16 };

int main(int argc, char *argv[]){
    printf("What is your name? ");
    char in_buffer[kBufferSize] = { 0 };
    if(safe_gets(in_buffer, kBufferSize, stdin) == NULL){
        printf("\nsafe_gets returned NULL.");
        return EXIT_FAILURE;
    }
    printf("Hello %s! Nice to meet you.", in_buffer);
    return EXIT_SUCCESS;
}

char *safe_gets(char *buf, int size, FILE *stream){
    if( fgets(buf, size, stream) ){
        for(int i = 0; i < size; i++){
            if('\n' == buf[i]){
                buf[i] = '\0';
                break;
            }
        }
        return buf;
    } else {
        return NULL;
    }
}
