#include <stdio.h>
#include <stdlib.h>
#include "../../headers/rstdin.h"

#define TAX_RATE .0550

int main(void) {
    enum {  num_items = 3 };

    int quant = 0;
    double price = 0;
    double subtotal = 0;
    
    int err = 0;    
    for(int i = 0; i < num_items; i++) {
        printf("Price of item %d: ", i+1);
        price = read_long_from_stdin_and_flush(NULL, &err);
        if(err != 0) {
            printf("Invalid number.");
            return EXIT_FAILURE;
        }

        printf("Quantity of item %d: ", i+1);
        quant = read_double_from_stdin_and_flush(NULL, &err);
        if(err != 0) {
            printf("Invalid number.");
            return EXIT_FAILURE;
        }
        
        subtotal += price * quant;
        price = quant = 0;
    }
    
    printf("Subtotal: $%.2lf\nTax: $%.2lf\nTotal: $%.2lf\n", subtotal, subtotal * TAX_RATE, (subtotal * TAX_RATE) + subtotal);
    return EXIT_SUCCESS;
}
