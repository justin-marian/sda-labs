#ifndef SORTED_LIST_H
#define SORTED_LIST_H

#include <stdlib.h>
#include <assert.h>

/*
    IMPORTANT!

    Since we use pure C, we cannot use templates.
    We assume that type T is previously defined.
*/

// -----------------------------------------------------------------------------
// Sorted List Structure
// -----------------------------------------------------------------------------

typedef struct node {
    T value;
    struct node* next;
} TNode, *TSortedList;

// -----------------------------------------------------------------------------
// Creating a List
// -----------------------------------------------------------------------------

/*
    Creates a new list with a single element.
*/
TSortedList create(T value) {
    TSortedList head = (TSortedList) malloc(sizeof(TNode));
    if (!head) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    head->value = value;
    head->next = NULL;
    return head;
}

/*
    Checks if the list is empty.
*/
int isEmpty(TSortedList list) {
    return (list == NULL);
}

// -----------------------------------------------------------------------------
// Checking If an Element Exists
// -----------------------------------------------------------------------------

/*
    Checks if a value exists in the list.
    Returns 1 if found, otherwise 0.
*/
int contains(TSortedList list, T value) {
    while (list) {
        if (list->value == value)
            return 1;
        list = list->next;
    }
    return 0;
}

// -----------------------------------------------------------------------------
// Inserting an Element in a Sorted List
// -----------------------------------------------------------------------------

/*
    Inserts an element into the sorted list while maintaining order.
*/
TSortedList insert(TSortedList list, T value) {
    TSortedList newNode = create(value);

    // Insert at the beginning
    if (!list || value < list->value) {
        newNode->next = list;
        return newNode;
    }

    TSortedList curr = list;
    while (curr->next && curr->next->value < value) {
        curr = curr->next;
    }

    newNode->next = curr->next;
    curr->next = newNode;

    return list;
}

// -----------------------------------------------------------------------------
// Deleting an Element
// -----------------------------------------------------------------------------

/*
    Deletes the first occurrence of a value from the list.
*/
TSortedList deleteOnce(TSortedList list, T value) {
    if (!list) return NULL;

    // Special case: first node is the target
    if (list->value == value) {
        TSortedList temp = list;
        list = list->next;
        free(temp);
        return list;
    }

    TSortedList curr = list;
    while (curr->next && curr->next->value != value) {
        curr = curr->next;
    }

    if (curr->next) {
        TSortedList temp = curr->next;
        curr->next = curr->next->next;
        free(temp);
    }

    return list;
}

// -----------------------------------------------------------------------------
// Getting the Length
// -----------------------------------------------------------------------------

/*
    Returns the length of the sorted list.
*/
long length(TSortedList list) {
    long len = 0;
    while (list) {
        len++;
        list = list->next;
    }
    return len;
}

// -----------------------------------------------------------------------------
// Getting the Nth Element
// -----------------------------------------------------------------------------

/*
    Returns the N-th element of the list (0-based index).
*/
int getNth(TSortedList list, unsigned int N) {
    unsigned int len = 1;

    while(list != NULL && len < N) {
        len++;
        list = list -> next;
    }
    return list -> value;
}


// -----------------------------------------------------------------------------
// Freeing the Sorted List
// -----------------------------------------------------------------------------

/*
    Frees the sorted list from memory and returns NULL.
*/
TSortedList freeTSortedList(TSortedList list) {
    while (list) {
        TSortedList temp = list;
        list = list->next;
        free(temp);
    }
    return NULL;
}

#endif
