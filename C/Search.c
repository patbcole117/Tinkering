#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int binary_search(int *arr, int start, int end, int target);
void get_sorted_list(int* arr, int len);
void get_unsorted_list(int* arr, int len, int seed, int max);
void print_list(int *arr, int len);
void selection_sort(int *arr, int len);

int main(int argc, char** argv){
    // Print usage information.
    if(argc == 1){
        printf("\n");
        printf("%s [ flags ] <search-item>\n", argv[0]);
        printf("-u <seed> -> unsorted list.\n");
        printf("-l <int> -> length of the list.\n");
        printf("-o <operation> -> type of operation.\n");
        printf("\t1. BinarySearch\n");
        printf("\n");
        return 0;
    }

    // Parse arguments.
    int len = 10, target = -1, rSeed = 0, oType = 1;
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
        if(!strcmp(argv[i], "-o")){
            sscanf(argv[i+1], "%d", &oType);
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

    // Do the thing.
    switch(oType){
        case 1: printf("Target: %d\n", target); binary_search(arr, 0, len-1, target); break;
        case 2: selection_sort(arr, len); break;
    }

    free(arr);
    return 1;
}

int binary_search(int *arr, int start, int end, int target){
    if(start > end){
        printf("Target not found.\n");
        return -1;
    }
    
    int middle = (start + end) / 2;
    if(target == arr[middle]){
        printf("Target found at index: %d.\n", middle);
        return middle;
    } else if(target > arr[middle]){
        return binary_search(arr, middle+1, end, target);
    } else {
        return binary_search(arr, start, middle-1, target);
    }
}

void selection_sort(int *arr, int len){
    for(int i = 0; i < len; i++){
        int mindex = i;
        for(int j = i; j < len; j++){
            if(arr[j] < arr[mindex]){
                mindex = j;
            }
        }
        //print_list(arr, len);
        if(arr[mindex] == arr[i]){
            continue;
        } else {
            arr[i]      = arr[mindex] ^ arr[i];
            arr[mindex] = arr[mindex] ^ arr[i];
            arr[i]      = arr[mindex] ^ arr[i];
        }
    }
    print_list(arr, len);
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