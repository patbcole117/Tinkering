#include <stdio.h>
#include <stdlib.h>

int read_ln(char *buf, int size, FILE *stream);

enum { kNumStr = 4, kBufSize = 32 };

int main(int argc, char *argv[]) {
    char libs[kNumStr][kBufSize];

    printf("Enter a noun: ");
    read_ln(libs[0], kBufSize, stdin);

    printf("Enter a verb: ");
    read_ln(libs[1], kBufSize, stdin);

    printf("Enter an adjective: ");
    read_ln(libs[2], kBufSize, stdin);

    printf("Enter an adverb: ");
    read_ln(libs[3], kBufSize, stdin);

    printf("Did you %s your %s %s %s?\n", libs[1], libs[2], libs[0], libs[3]);

    return EXIT_SUCCESS;
}

int read_ln(char *buf, int size, FILE *stream) {
    char ch;
    int i = 0, ch_remains = 1;
    while( ch_remains ) {
        ch = fgetc(stream);
        if((ch == '\n') || (ch == EOF)) {
            ch_remains = 0;
        } else if (i < size-1) {
            *(buf+i) = ch;
            i++;
        } 
    }
    *(buf+i) = '\0';
    return i+1;
}