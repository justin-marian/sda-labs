#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_INPUT_LEN 256

typedef int Item;

#include "include/Queue.h"

void printArray(int *arr, int len) {
    for (int i = 0; i < len; i++)  
        printf("%d ", arr[i]);
    printf("\n");
}

/// Returns the maximum number in an array
int arrayMaximum(const int* arr, int len) {
    int max = arr[0];
    for (int i = 1; i < len; i++) {
        if (arr[i] > max) 
            max = arr[i];
    }
    return max;
}

/// Returns the number of digits in a given number
int getNumberOfDigits(int num) {
    if (num == 0) return 1;
    int digits = 0;
    while (num) {
        num /= 10;
        digits++;
    }
    return digits;
}

/// Performs Radix Sort on an integer array
void radixSort(int *arr, int len) {
    int p = 10;

    // Declare an array of Queue pointers
    Queue* queue[10]; 

    // Initialize each queue
    for (int i = 0; i < 10; i++) {
        queue[i] = createQueue();
    }

    int n = getNumberOfDigits(arrayMaximum(arr, len));

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < len; j++) {
            int digit = (arr[j] % p) / (p / 10);
            enqueue(queue[digit], arr[j]);  
        }

        p *= 10;
        int index = 0;

        for (int k = 0; k < 10; k++) {
            while (!isQueueEmpty(queue[k])) {  
                arr[index++] = front(queue[k]); 
                dequeue(queue[k]);              
            }
        }
    }

    // Free memory for queues
    for (int i = 0; i < 10; i++) {
        destroyQueue(queue[i]);  
    }
}


int main(void) {
    char fileBuffer[MAX_INPUT_LEN];
    FILE* inputFile = fopen("../data/input-radix-sort.csv", "r");

    if (!inputFile) {
        fprintf(stderr, "Error: Unable to open input file.\n");
        return EXIT_FAILURE;
    }

    int capacity = MAX_INPUT_LEN;
    int *arr = (int*) malloc(capacity * sizeof(int));
    if (!arr) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        fclose(inputFile);
        return EXIT_FAILURE;
    }

    int count = 0;
    while (fgets(fileBuffer, MAX_INPUT_LEN, inputFile) != NULL) {
        fileBuffer[strcspn(fileBuffer, "\r\n")] = 0;
        int len = 0;
        
        char *token = strtok(fileBuffer, ",");
        while (token) {
            if (len == capacity) {
                capacity *= 2;
                arr = realloc(arr, capacity * sizeof(int));
                if (!arr) {
                    fprintf(stderr, "Error: Memory reallocation failed.\n");
                    fclose(inputFile);
                    return EXIT_FAILURE;
                }
            }
            arr[len++] = atoi(token);
            token = strtok(NULL, ",");
        }

        if (len > 0) {
            count++;
            printf("Input array %d:\t", count);
            printArray(arr, len);
            
            radixSort(arr, len);
            
            printf("Sorted array %d:\t", count);
            printArray(arr, len);
            printf("\n");
        }
    }

    free(arr);
    fclose(inputFile);
    return EXIT_SUCCESS;
}
