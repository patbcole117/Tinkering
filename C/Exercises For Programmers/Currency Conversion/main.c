#include <stdio.h>
#include <stdlib.h>
#include "../../headers/rstdin.h"

int main(void){
    int err = 0;
    printf("How many euros: ");
    double num_euros = read_double_from_stdin_and_flush(NULL, &err);    
    if(err != 0){
        printf("Invalid number of euros.\n");
        return EXIT_FAILURE;
    }

    printf("What is the exchange rate: ");
    double xchg_rate = read_double_from_stdin_and_flush(NULL, &err);    
    if(err != 0){
        printf("Invalid exchange rate.\n");
        return EXIT_FAILURE;
    }

    printf("%.2lf euros at an exchange rate of %.3lf is\n$%.2lf U.S. Dollars.\n", num_euros, xchg_rate, num_euros * xchg_rate);
    return EXIT_SUCCESS;
}
