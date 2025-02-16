#include <stdio.h>
#include <stdlib.h>

typedef struct OrderedSet {
    T* elements;
    long size;
    long capacity;
} OrderedSet;

/*
  Function to create an ordered set with an initial capacity.
  Returns a pointer to the created set or NULL in case of failure.
*/
OrderedSet* createOrderedSet(long initialCapacity) {
    if (initialCapacity <= 0) {
        fprintf(stderr, "Error: Initial capacity must be greater than 0.\n");
        return NULL;
    }

    // Allocate memory for the OrderedSet struct
    OrderedSet* newSet = (OrderedSet*) malloc(sizeof(OrderedSet));
    if (!newSet) {
        fprintf(stderr, "Error: Memory allocation failed for OrderedSet.\n");
        return NULL;
    }

    // Allocate memory for the elements
    newSet->elements = (T*) malloc(initialCapacity * sizeof(T));
    if (!newSet->elements) {
        fprintf(stderr, "Error: Memory allocation failed for elements.\n");
        free(newSet);
        return NULL;
    }

    // Initialize fields
    newSet->size = 0;
    newSet->capacity = initialCapacity;

    return newSet;
}
