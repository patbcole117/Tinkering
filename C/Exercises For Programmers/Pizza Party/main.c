#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int read_long(long *l, FILE *stream);
enum { kBufSize = 8 };

int main(int argc, char *argv[]) {
    long num_people = 0;
    printf("How many people? ");
    if(read_long(&num_people, stdin) == -1) {
        printf("Cannot covert input to num_people.\n");
        return EXIT_FAILURE;
    }    

    long num_pizzas = 0;
    printf("How many pizzas? ");
    if(read_long(&num_pizzas, stdin) == -1) {
        printf("Cannot covert input to num_pizzas.\n");
        return EXIT_FAILURE;
    }

    long num_slices = 0;
    printf("How many slices per pizza? ");
    if(read_long(&num_slices, stdin) == -1) {
        printf("Cannot covert input to num_slices.\n");
        return EXIT_FAILURE;
    }
    
    printf("People: %ld\nPizzas: %ld\nSlices: %ld\n", num_people, num_pizzas, num_slices);
    printf("Each person gets %ld slices.\n", (num_pizzas * num_slices) / num_people);
    printf("There are %ld slices leftover.\n", (num_pizzas * num_slices) % num_people);

    num_people, num_pizzas, num_slices = 0, 0, 0;
    return EXIT_SUCCESS;
}

int read_long(long *l, FILE *stream) {
    char ch = '\0';
    int i = 0;
    char in_buf[kBufSize] = { 0 };
    while( 1 ) {
        ch = fgetc(stream);
        if((ch == '\n') || (ch == EOF)) {
            break;
        } else if(i < sizeof(in_buf)-1) {
            if(isdigit(ch)) {
                *(in_buf+i) = ch;
                i++;
            } else {
                ch = '\0';
                memset(in_buf, 0, sizeof(in_buf));
                return -1;
            }
        }
    }
    *(in_buf+i) = '\0';
    ch = '\0';
    *l = strtol(in_buf, NULL, 10);
    memset(in_buf, 0, sizeof(in_buf));
    return i+1; 
}
