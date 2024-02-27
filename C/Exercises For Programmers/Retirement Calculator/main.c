#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

int read_ln(char *buf, int size, FILE *stream);

enum { kNumBufSize = 8 };

int main(int argc, char *argv[]) {
    char *end = { 0 };

    char age_buf[kNumBufSize] = { 0 };
    printf("What is your current age? ");
    read_ln(age_buf, kNumBufSize, stdin);
    long long age = strtoll(age_buf, &end, 10);
    memset(age_buf, 0, sizeof(age_buf));

    char ret_buf[kNumBufSize] = { 0 };
    printf("At what age would you like to retire? ");
    read_ln(ret_buf, kNumBufSize, stdin);
    long long ret = strtoll(ret_buf, &end, 10);
    memset(ret_buf, 0, sizeof(ret_buf));

    printf("You have %lld years left until you can retire.\n", ret-age);

    time_t time_now = time(NULL);
    if(time_now == (time_t)(-1)) {
        printf("Time returned -1.\n");
        return EXIT_FAILURE;
    }

    struct tm *gmt = gmtime(&time_now);
    printf("It is  %d, so you can retire in %lld.\n", gmt->tm_year+1900, gmt->tm_year+1900+ret-age);
    memset(gmt, 0, sizeof(gmt));
    memset(&time_now, 0, sizeof(time_now));
        
    return EXIT_SUCCESS;
}

int read_ln(char *buf, int size, FILE *stream) {
    char ch = '\0';
    int i = 0;
    while( 1 ) {
        ch = fgetc(stream);
        if((ch == '\n') || (ch == EOF)) {
            break;
        } else if(i < size-1) {
            *(buf+i) = ch;
            i++;
        }
    }
    *(buf+i) = '\0';
    return i+1;
}
