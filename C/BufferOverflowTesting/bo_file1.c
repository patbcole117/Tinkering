#include <stdlib.h>
#include <stdio.h>

int bof1(){
    char buffer[8];
    FILE *badfile;

    badfile = fopen("badfile", "r");
    fread(buffer, sizeof(char), 1024, badfile);

    return 1;
}

int main(int argc, char **argv){
    bof1();
    printf("Exploit failed!");
    return 1;
}
