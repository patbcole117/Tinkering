#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

enum { kBufsize = 64 };

int main(int argc, char *argv[]) {
    char in_buf[kBufsize] = { 0 };
    char *end = '\0';

    printf("Enter x: ");
    read_ln(in_buf, kBufsize, stdin);
    long long x = strtoll(in_buf, &end, 10);
    memset(in_buf, '\0', kBufsize*sizeof(char));
    
    printf("Enter y: ");
    read_ln(in_buf, kBufsize, stdin);
    long long y = strtoll(in_buf, &end, 10);
    memset(in_buf, '\0', kBufsize*sizeof(char));

    printf("x + y = %lld\n", x+y);
    printf("x - y = %lld\n", x-y);
    printf("x * y = %lld\n", x*y);
    printf("x / y = %lld r%lld\n", x/y, x%y);

    return EXIT_SUCCESS;
}

int read_ln(char *buf, int size, FILE *stream) {
    char ch;
    int i = 0;
    while( 1 ) {
        ch = fgetc(stream);
        if((ch == '\n') || (ch == EOF)) {
            break;
        } else if (i < size-1) {
            *(buf+i) = ch;
            i++;
        }
    }
    *(buf+i) = '\0';
    return i+1;
}