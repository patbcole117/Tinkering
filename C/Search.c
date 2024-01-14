#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void get_sorted_list(int* arr, int len);
void get_unsorted_list(int* arr, int len, int seed, int max);
void print_list(int *arr, int len);

int main(int argc, char** argv){
    // Print usage information.
    if(argc == 1){
        printf("\n");
        printf("%s [ flags ] <search-item>\n", argv[0]);
        printf("-u <seed> -> unsorted list.\n");
        printf("-l <int> -> length of the list.\n");
        printf("-s <search type> -> type of search.\n");
        printf("\t1. BinarySearch\n");
        printf("\n");
        return 0;
    }

    // Parse arguments.
    int len = 10, target = -1, rSeed = 0, sType = 1;
    for(int i = 1; i < argc; i++){
        if(!strcmp(argv[i], "-u")){
            sscanf(argv[i+1], "%d", &rSeed);
            i++;
            continue;
        }
        if(!strcmp(argv[i], "-l")){
            sscanf(argv[i+1], "%d", &len);
            i++;
            continue;
        }
        if(!strcmp(argv[i], "-s")){
            sscanf(argv[i+1], "%d", &sType);
            i++;
            continue;
        }
        sscanf(argv[i], "%d", &target);
    }

    // Allocate, fill, and print list.
    int *arr = malloc(len * sizeof(int));
    if(rSeed){
        get_unsorted_list(arr, len, rSeed, 10);
    } else {
        get_sorted_list(arr, len);
    }
    print_list(arr, len);
    printf("target: %d\n", target);

    free(arr);
    return 1;
}

void get_unsorted_list(int* arr, int len, int seed, int max){
     srand(seed);
    for(int i = 0; i < len; i++){
        arr[i] = (rand() % max);
    }
}

void get_sorted_list(int* arr, int len){
    for(int i = 0; i < len; i++){
        arr[i] = i;
    }
}

void print_list(int *arr, int len){
    printf("\n[%d", arr[0]);
    for(int i = 1; i < len; i++){
        printf(", %d", arr[i]);
    }
    printf("]\n");
}