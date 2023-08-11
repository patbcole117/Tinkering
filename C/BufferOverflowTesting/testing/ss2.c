#include <string.h>

void function(char *str){
    char buffer[16];
    strcpy(buffer,str);
}

void main(void){
    char large_string[32];
    int i;

    for(i=0;i<28;i++){
        large_string[i]='A';
    }

    for(i=28;i<32;i++){
        large_string[i]='B';
    }

    function(large_string);
}
