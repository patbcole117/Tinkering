#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { kBufSize = 8 };
int read_ln(char *buf, int size, FILE *stream);


int main(int argc, char *argv[]){
    printf("What is the quote? ");
    char quote_buf[kBufSize] = { 0 };
    int res1 = read_ln(quote_buf, kBufSize, stdin);

    printf("Who said it? ");
    char auth_buf[kBufSize] = { 0 };
    int res2 =read_ln(auth_buf, kBufSize, stdin);

    printf("\"%s\" - %s\n", quote_buf, auth_buf);
    printf("size of quote_buf: %d\n", res1);
    printf("size of auth_buf: %d\n", res2);
    return EXIT_SUCCESS;
}

int read_ln(char *buf, int size, FILE *stream) {
    char ch;
    int i = 0;
    int chars_remain = 1;
    while( chars_remain ) {
        ch = fgetc(stream);
        if ((ch == '\n') || (ch == EOF)) {
            chars_remain = 0;
            *(buf+i) = '\0';
        } else if (i < size-1) {
            *(buf+i) = ch;
            i++;
        }
    }
    *(buf+i) = '\0';
    return i+1;
}
