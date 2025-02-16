#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef char T;

#include "include/OrderedSet.h"

/*
  Function that returns an ordered set containing unique characters
  from the given word.
*/
OrderedSet* letters(const char *word) {
    if (!word) return NULL;

    long len = strlen(word);
    OrderedSet* set = createOrderedSet(len);
    if (!set) {
        fprintf(stderr, "Memory allocation failed for OrderedSet.\n");
        return NULL;
    }

    for (long idx = 0; idx < len; idx++) {
        add(set, word[idx]);
    }

    return set;
}

/*
  Function that prints the size and elements of an ordered set.
*/
void printOrderedCharSet(const OrderedSet* set) {
    if (!set) {
        printf("Set is NULL or empty.\n");
        return;
    }

    printf("There are %ld letters:", set->size);
    for (long idx = 0; idx < set->size; idx++) {
        printf(" %c", set->elements[idx]);
    }
    printf("\n");
}

int main(void) {
    OrderedSet *s1, *s2, *sU, *sI;

    s1 = letters("mississippi");
    printf("mississippi: ");
    printOrderedCharSet(s1);

    s2 = letters("small");
    printf("small: ");
    printOrderedCharSet(s2);

    sU = unionOrderedSets(s1, s2);
    printf("Union: ");
    printOrderedCharSet(sU);

    sI = intersectOrderedSets(s1, s2);
    printf("Intersection: ");
    printOrderedCharSet(sI);

    return 0;
}
