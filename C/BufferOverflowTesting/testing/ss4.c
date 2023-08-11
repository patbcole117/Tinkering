#include <stdio.h>
#include <string.h>

void function(int a, int b, int c){
    char buffer1[5] = {'A', 'A', 'A', 'A', 'A'};
    int *ret;

    ret = buffer1 + 32;
    (*ret) += 12;
}

void main(){
    int x;

    x = 0;
    function(1,2,3);
    x = 1;
    printf("%d\n",x);
}
