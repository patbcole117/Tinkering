#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "rstdin.h"

int main(void) {
    printf("Please enter a long: ");
    int err = { 0 };
    long l1 = read_long_from_stdin_and_flush(NULL, &err);
    if(err != 0)
        return EXIT_FAILURE;
    
    printf("Enter another long: ");
    long l2 = read_long_from_stdin_and_flush(NULL, &err);
    if(err != 0)
        return EXIT_FAILURE;

    printf("You entered ( l1 = %ld ) ( l2 = %ld ).\n", l1, l2);

    printf("Please enter a double: ");
    double d1 = read_double_from_stdin_and_flush(NULL, &err);
    if(err != 0)
        return EXIT_FAILURE;
    
    printf("Enter another double: ");
    double d2 = read_double_from_stdin_and_flush(NULL, &err);
    if(err != 0)
        return EXIT_FAILURE;

    printf("You entered ( d1 = %lf ) ( d2 = %lf ).\n", d1, d2);

    enum { szbuf = 64 };
    printf("Please enter a string: ");
    char buf[szbuf] = { 0 };
    int r = read_string_from_stdin_and_flush(szbuf, buf);
    printf("Read %d characters from stdin.\n", r);
    printf("Echo: %s\n", buf);

    r = 0;
    memset(buf, 0, sizeof(buf));
    
    printf("Please enter a string: ");
    r = read_string_from_stdin_and_flush(szbuf, buf);
    printf("Read %d characters from stdin.\n", r);
    printf("Echo: %s\n", buf);
    memset(buf, 0, sizeof(buf));
    
    return EXIT_SUCCESS;
}
