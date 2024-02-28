#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>

enum { szInBuf = 32 };

int read_string_from_stdin_and_flush(int size, char *str_buf) {
    char ch = { 0 };
    int i = { 0 };
    while( 1 ) {
        ch = fgetc(stdin);
        if((ch == '\n') || (ch == EOF)) {
            break;
	    }
        if(i < size - 1) {
	        *(str_buf+i) = ch;
	        i++;
        }
    }
    *(str_buf+i) = '\0';
    return i+1;
}

double read_double_from_stdin_and_flush(int *idx, int *err) {
    char in_buf[szInBuf] = { 0 };
    char ch = { 0 };
    int i = { 0 };
    while( 1 ) {
        ch = fgetc(stdin);
        if((ch == '\n') || (ch == EOF)) {
            break;
	    }
        if(i < szInBuf - 1) {
	        *(in_buf+i) = ch;
	        i++;
        }
    }
    *(in_buf+i) = '\0';

    double d = strtod(in_buf, NULL);
    memset(in_buf, 0,  sizeof(in_buf));
    if(errno == ERANGE) {
        *err = -1;
    }
    if(idx != NULL) {
        *idx = i;
    }
    return d;
}

long read_long_from_stdin_and_flush(int *idx, int *err) {
    char in_buf[szInBuf] = { 0 };
    char ch = { 0 };
    int i = { 0 };
    while( 1 ) {
        ch = fgetc(stdin);
        if((ch == '\n') || (ch == EOF)) {
            break;
	    }
	    if(i < szInBuf-1) {
	        *(in_buf+i) = ch;
	        i++;
        }
    }
    *(in_buf+i) = '\0';

    long l = strtol(in_buf, NULL, 10);
    memset(in_buf, 0,  sizeof(in_buf));
    if(errno == ERANGE) {
        *err = -2;
    }
    if(idx != NULL) {
        *idx = i;
    }
    return l;
}
