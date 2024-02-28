#include <stdio.h>
#include <stdlib.h>
#include "../../headers/rstdin.h"

int main(void) {
    enum { GalToSqFt = 350 };
    int err = 0;

    printf("Enter length: ");
    long length = read_long_from_stdin_and_flush(NULL, &err);
    if(err == -1) {
        printf("read_long err ( -1 ): Failed to convert input to long!.\n");
        return EXIT_FAILURE;
    } 
    if( err == -2 ) {
        printf("read_long err ( -2 ): Number is outside range!\n");
	    return EXIT_FAILURE;
    }
    
    printf("Enter width: ");
    long width = read_long_from_stdin_and_flush(NULL, &err);
    if(err == -1) {
        printf("read_long err ( -1 ): Failed to convert input to long!.\n");
        return EXIT_FAILURE;
    } 
    if( err == -2 ) {
        printf("read_long err ( -2 ): Number is outside range!\n");
	    return EXIT_FAILURE;
    } 
    
    long area = length * width;
    long cans_needed = area % GalToSqFt == 0 ? (area / GalToSqFt) : (area / GalToSqFt) + 1;
    
    printf("You will need to purchase %ld cans of paint to cover %ld square feet.\n", cans_needed, area);

    return EXIT_SUCCESS;
}
