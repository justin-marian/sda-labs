#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node {
    long value;
    struct node* next;
} Node, *List;

/*
    Function to create a large linked list of given size.
*/
List createHugeList(long size) {
    if (size <= 0) return NULL;

    List list = (Node*) malloc(sizeof(Node));
    if (!list) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    
    list->value = 0l;
    List aux = list;

    for (long idx = 1l; idx < size; idx++) {
        aux->next = (Node*) malloc(sizeof(Node));
        if (!aux->next) {
            fprintf(stderr, "Error: Memory allocation failed.\n");
            exit(EXIT_FAILURE);
        }
        aux = aux->next;
        aux->value = (idx % 5l) - 2l;
    }
    aux->next = NULL;
    return list;
}

/*
    Function to free the linked list memory.
*/
void deleteHugeList(List list) {
    while (list) {
        List temp = list;
        list = list->next;
        free(temp);
    }
}

/*
    Iterative function to compute list length.
*/
long lengthIterative(List list) {
    long l = 0;
    while (list) {
        l++;
        list = list->next;
    }
    return l;
}

/*
    Standard recursive function (prone to stack overflow for large lists).
*/
long lengthStackRecursive(List list) {
    if (!list) return 0;
    return 1 + lengthStackRecursive(list->next);
}

/*
    Helper function for tail recursion.
*/
long accumulator(List list, long acc) {
    if (!list) return acc;
    return accumulator(list->next, acc + 1);
}

/*
    Tail recursive function (safe for large lists).
*/
long lengthTailRecursive(List list) {
    return accumulator(list, 0);
}

/*
    Function to evaluate execution time of a length function.
*/
void evalLengthFunction(long SIZE, const char* name, long (*lengthFunc)(List)) {
    clock_t t0, t1;
    List list = createHugeList(SIZE);
    t0 = clock();
    long size = (*lengthFunc)(list);
    t1 = clock();
    deleteHugeList(list);
    printf("Size: %ld | %20s: %.6lf sec\n", size, name, (double)(t1 - t0) / CLOCKS_PER_SEC);
}

int main() {
    static const long SIZE = 200000l; // Size of the list

    evalLengthFunction(SIZE, "Iterative", &lengthIterative);
    evalLengthFunction(SIZE, "Tail Recursive", &lengthTailRecursive);
    evalLengthFunction(SIZE, "Stack Recursive", &lengthStackRecursive);

    return 0;
}
