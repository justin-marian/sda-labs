#include <stdio.h>
#include <stdlib.h>

#include "include/stack.h"

/**
 * Initializes a new stack node with the given data.
 * Returns the newly created stack node or NULL if allocation fails.
 */
Stack initStack(E data) {
    Stack s = (Stack) malloc(sizeof(struct stack));
    if (!s) {
        fprintf(stderr, "Error: Memory allocation failed for stack node.\n");
        return NULL;
    }
    s->data = data;
    s->next = NULL;
    return s;
}

/**
 * Pushes an element onto the stack.
 * Returns the new stack top.
 */
Stack push(Stack s, E data) {
    Stack newNode = initStack(data);
    if (!newNode) return s;
    newNode->next = s;
    return newNode;
}

/**
 * Pops the top element from the stack.
 * Returns the new stack top.
 */
Stack pop(Stack s) {
    if (isEmptyStack(s)) return NULL;
    Stack tmp = s;
    s = s->next;
    free(tmp);
    return s;
}

/**
 * Returns the top element of the stack without removing it.
 * Returns -1 if the stack is empty.
 */
E top(Stack s) {
    if (isEmptyStack(s)) {
        fprintf(stderr, "Warning: Trying to access top of an empty stack.\n");
        return -1;
    }
    return s->data;
}

/**
 * Checks if the stack is empty.
 * Returns 1 if empty, 0 otherwise.
 */
int isEmptyStack(Stack s) {
    return s == NULL;
}

/**
 * Frees all nodes in the stack.
 * Returns NULL after freeing.
 */
Stack freeStack(Stack s) {
    while (s) {
        Stack tmp = s;
        s = s->next;
        free(tmp);
    }
    return NULL;
}
