#include <stdio.h>
#include "allocator.h"


void testMalloc() {
    printf("Testing malloc...\n");
    char *str = (char*)malloc(20 * sizeof(char));
    if (str) {
        snprintf(str, 20, "Hello, World!");
        printf("%s\n", str);
        free(str);
        printf("Malloc successful\n");
    } else {
        printf("Memory allocation failed\n");
    }
}

void testCalloc() {
    printf("Testing calloc...\n");
    int *arr = (int*)calloc(5, sizeof(int));
    if (arr) {
        for (int i = 0; i < 5; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
        free(arr);
        printf("Calloc successful\n");
    } else {
        printf("Memory allocation failed\n");
    }
}

void testRealloc() {
    printf("Testing realloc...\n");
    char *str = (char*)malloc(10 * sizeof(char));
    if (str) {
        snprintf(str, 10, "Hello");
        printf("%s\n", str);
        str = (char*)realloc(str, 20 * sizeof(char));
        if (str) {
            snprintf(str, 20, "Hello, World!");
            printf("%s\n", str);
            free(str);
            printf("Realloc successful\n");
        } else {
            printf("Memory allocation failed\n");
        }
    }
}

int main() {
  
    testMalloc();
    testCalloc();
    testRealloc();
    return 0;
}