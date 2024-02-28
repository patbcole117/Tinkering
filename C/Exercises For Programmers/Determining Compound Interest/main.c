#include <stdio.h>
#include <stdlib.h>
#include "../../headers/rstdin.h"
#include <math.h>

int main(void){
    int err = 0;
    printf("Enter principal: ");
    double prncpl = read_double_from_stdin_and_flush(NULL, &err);
    if(err != 0){
        printf("Invalid principal.\n");
        return EXIT_FAILURE;
    }

    printf("Enter rate of interest: ");
    double rate_of_interest = read_double_from_stdin_and_flush(NULL, &err) / 100;
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

    printf("Enter number of times the interest compounds per year: ");
    long rate_cmpnd = read_long_from_stdin_and_flush(NULL, &err);
    if(err != 0){
        printf("Invalid number of times per year.\n");
        return EXIT_FAILURE;
    }

    double total = prncpl * pow((1 + (rate_of_interest/rate_cmpnd)), (rate_cmpnd*num_years));
    printf("$%.2lf invested at %.3lf%% for %ld years compounded %ld times per year will be worth $%.2lf.\n", prncpl, rate_of_interest*100, num_years, rate_cmpnd, total);

    return EXIT_SUCCESS;
}
