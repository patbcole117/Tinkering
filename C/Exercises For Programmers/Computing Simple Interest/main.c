#include <stdio.h>
#include <stdlib.h>
#include "../../headers/rstdin.h"

int main(void){
    int err = 0;
    printf("Enter principal: ");
    double prncpl = read_double_from_stdin_and_flush(NULL, &err);
    if(err != 0){
        printf("Invalid principal.\n");
        return EXIT_FAILURE;
    }

    printf("Enter rate of interest: ");
    double rate_of_interest = read_double_from_stdin_and_flush(NULL, &err);
    if(err != 0){
        printf("Invalid rate of interest.\n");
        return EXIT_FAILURE;
    }

    printf("Enter number of years: ");
    long num_years = read_long_from_stdin_and_flush(NULL, &err);
    if(err != 0){
        printf("Invalid number of years.\n");
        return EXIT_FAILURE;
    }

    printf("After %ld years at %.3lf%%, the investment will be worth $%.2lf.\n", num_years, rate_of_interest, prncpl * (1 + num_years * rate_of_interest / 100));
    return EXIT_SUCCESS;
}
