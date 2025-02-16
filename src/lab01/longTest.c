#include <stdio.h>
#include <stdlib.h>

typedef long T;

#include "include/OrderedSet.h"

/*
  Function that returns an ordered set with numbers between `inc` and `fin`
  that are multiples of `nr`.
*/
OrderedSet* cifre(long inc, long fin, long nr) {
    if (nr == 0 || inc > fin) return NULL;

    long k = 0, idx;
    
    // Count how many numbers are multiples of `nr` within the range
    for (idx = inc; idx <= fin; idx++)
        if (idx % nr == 0) k++;

    // Create an ordered set with the exact number of elements
    OrderedSet* array = createOrderedSet(k);
    if (!array) {
        fprintf(stderr, "Error allocating OrderedSet.\n");
        return NULL;
    }

    // Populate the ordered set with valid multiples of `nr`
    for (idx = inc; idx <= fin; idx++)
        if (idx % nr == 0) 
            add(array, idx);

    return array;
}

/*
  Function that prints the size and elements of an ordered set.
*/
void printOrderedLongArray(const OrderedSet* array) {
    if (!array || array->size == 0) {
        printf("The set is empty.\n");
        return;
    }

    printf("There are %ld elements:", array->size);
    for (long idx = 0; idx < array->size; idx++)
        printf(" %ld", array->elements[idx]);
    printf("\n");
}

int main(void) {
    OrderedSet *s1, *s2, *sU, *sI;

    s1 = cifre(4, 25, 3);
    printf("Multiples of 3 in the range [4, 25]:\n ");
    printOrderedLongArray(s1);

    s2 = cifre(5, 30, 4);
    printf("Multiples of 4 in the range [5, 30]:\n ");
    printOrderedLongArray(s2);

    sU = unionOrderedSets(s1, s2);
    printf("Union: ");
    printOrderedLongArray(sU);

    sI = intersectOrderedSets(s1, s2);
    printf("Intersection: ");
    printOrderedLongArray(sI);

    return 0;
}
