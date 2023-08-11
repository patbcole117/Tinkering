#include <stdio.h>
#include <string.h>

int display(char *input);

int main(int argc, char *argv[]){
    display(argv[1]);
    return 0;
}

int display(char *input){
    while(*input != '\0'){
        printf("%c\n", *input);
        input += 1;
    }
    return 0;
}
