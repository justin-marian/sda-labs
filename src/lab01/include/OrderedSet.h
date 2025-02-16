#ifndef ORDERED_SET_H
#define ORDERED_SET_H

#include <stdio.h>
#include <stdlib.h> 

/*
  IMPORTANT!

  Since we are using pure C, we cannot use templates. We assume
  that some type T has been previously defined.
*/

#include "OrderedArray.h"

// -----------------------------------------------------------------------------
// Element Search (Binary Search)
// -----------------------------------------------------------------------------

/*
  Function to check if an element exists in the set.
  Uses binary search since the elements are ordered.

  Returns 1 if found, otherwise returns 0.
*/
int contains(const OrderedSet* set, const T element) {
    if (!set || set->size == 0) return 0;

    int l = 0, r = set->size - 1, m;
    while (l <= r) {
        m = l + (r - l) / 2;
        if (set->elements[m] == element) return 1;
        if (element < set->elements[m]) r = m - 1;
        else l = m + 1;
    }
    return 0;
}

// -----------------------------------------------------------------------------
// Adding an Element to the Ordered Set
// -----------------------------------------------------------------------------

/*
  Adds a new element to the set while maintaining order.
  If the element already exists, nothing changes.
*/
void add(OrderedSet* set, const T newElement) {
    if (!set) return;

    if (contains(set, newElement)) return; // Avoid duplicates

    if (set->size >= set->capacity) { // Expand memory if full
        long newCapacity = set->capacity * 2;
        T* temp = (T*) realloc(set->elements, newCapacity * sizeof(T));
        if (!temp) {
            fprintf(stderr, "Error: Memory reallocation failed.\n");
            return;
        }
        set->elements = temp;
        set->capacity = newCapacity;
    }

    // Insert while maintaining order
    long i = set->size - 1;
    while (i >= 0 && set->elements[i] > newElement) {
        set->elements[i + 1] = set->elements[i]; // Shift elements right
        i--;
    }
    
    set->elements[i + 1] = newElement;
    set->size++;
}

// -----------------------------------------------------------------------------
// Union of Two Ordered Sets
// -----------------------------------------------------------------------------

/*
  Returns a new ordered set that represents the union of two sets.
*/
OrderedSet* unionOrderedSets(const OrderedSet* s1, const OrderedSet* s2) {
    if (!s1 || !s2) return NULL;

    OrderedSet* set = createOrderedSet(s1->size + s2->size);
    if (!set) return NULL;

    int i = 0, j = 0, k = 0;

    while (i < s1->size && j < s2->size) {
        if (s1->elements[i] < s2->elements[j])
            set->elements[k++] = s1->elements[i++];
        else if (s1->elements[i] > s2->elements[j])
            set->elements[k++] = s2->elements[j++];
        else { // Avoid duplicates
            set->elements[k++] = s1->elements[i++];
            j++;
        }
    }

    while (i < s1->size) set->elements[k++] = s1->elements[i++];
    while (j < s2->size) set->elements[k++] = s2->elements[j++];

    set->size = k; // Update final size
    return set;
}

// -----------------------------------------------------------------------------
// Intersection of Two Ordered Sets
// -----------------------------------------------------------------------------

/*
  Returns a new ordered set that represents the intersection of two sets.
*/
OrderedSet* intersectOrderedSets(const OrderedSet* s1, const OrderedSet* s2) {
    if (!s1 || !s2) return NULL;

    OrderedSet* set = createOrderedSet((s1->size < s2->size) ? s1->size : s2->size);
    if (!set) return NULL;

    int i = 0, j = 0, k = 0;

    while (i < s1->size && j < s2->size) {
        if (s1->elements[i] == s2->elements[j]) {
            set->elements[k++] = s1->elements[i++];
            j++;
        } else if (s1->elements[i] < s2->elements[j]) {
            i++;
        } else {
            j++;
        }
    }

    set->size = k;
    return set;
}

// -----------------------------------------------------------------------------
// Free Memory
// -----------------------------------------------------------------------------

/*
  Function to free the memory used by an OrderedSet.
*/
void destroyOrderedSet(OrderedSet* set) {
    if (!set) return;
    free(set->elements);
    free(set);
}

#endif
