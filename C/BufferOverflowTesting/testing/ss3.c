#include <string.h>
#include <stdio.h>

void function(char *str){
    char buffer[16];
    strcpy(buffer, str);
    printf("\n%s\n\n", buffer);
}

void main(int argc, char *argv[]){
    function(argv[1]);
}
