#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int read_ln(char *buf, int size, FILE *stream);

enum { kBufSize = 8 };
const double kFeetToMeters = 0.3048;

int main(int argc, char *argv[]) {
    char in_buf[kBufSize] = { 0 };
    printf("What is the length: ");
    read_ln(in_buf, kBufSize, stdin);
    double l = strtod(in_buf, NULL);
    memset(in_buf, 0, sizeof(in_buf));

    printf("What is the width: ");
    read_ln(in_buf, kBufSize, stdin);
    double w = strtod(in_buf, NULL);
    memset(in_buf, 0, sizeof(in_buf));

    printf("Dimentions: %.3f x %.3f ( feet )\n", l, w);
    printf("The area is: %.3f ( feet^2 )\n", l*w);
    
    printf("Dimentions: %.3f x %.3f ( meters )\n", kFeetToMeters * l, kFeetToMeters * w);
    printf("The area is: %.3f ( meters^2 )\n", kFeetToMeters * (l*w));
    l = 0;
    w = 0;
    return EXIT_SUCCESS;
}

int read_ln(char * buf, int size, FILE *stream) {
    char ch = '\0';
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
    ch = '\0';
    return i+1;
}
