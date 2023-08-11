#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    char *args, *s1, *s2;
    char buffer[128];
    int i;

    args = argv[1];
    s1 = "/bin/ls";
    s2 = "/bin/ps";

    if(argc>1){
        for(i=0; i<=128; i++){
            buffer[i] = args[i];
        }
    }

    system(s2);

    return 0;

}
