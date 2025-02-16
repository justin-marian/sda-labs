#ifndef STACK_H_
#define STACK_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct StackNode {
    Item elem;
    struct StackNode *next;
} StackNode;

typedef struct Stack {
    StackNode* head;
    long size;
} Stack;

// -----------------------------------------------------------------------------
// Function: createStack
// Purpose:  Creates a new empty stack
// -----------------------------------------------------------------------------
Stack* createStack(void) {
    Stack* stack = (Stack*) malloc(sizeof(Stack));
    if (stack == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for stack.\n");
        exit(EXIT_FAILURE);
    }

    stack->size = 0;
    stack->head = NULL;
    return stack;
}

// -----------------------------------------------------------------------------
// Function: isStackEmpty
// Purpose:  Checks if the stack is empty
// -----------------------------------------------------------------------------
int isStackEmpty(Stack* stack) {
    return (stack == NULL || stack->head == NULL);
}

// -----------------------------------------------------------------------------
// Function: push
// Purpose:  Adds an element to the top of the stack
// -----------------------------------------------------------------------------
void push(Stack *stack, Item elem) {
    if (stack == NULL) {
        fprintf(stderr, "Error: Cannot push to a NULL stack.\n");
        return;
    }

    StackNode* newNode = (StackNode*) malloc(sizeof(StackNode));
    if (newNode == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for stack node.\n");
        exit(EXIT_FAILURE);
    }

    newNode->elem = elem;
    newNode->next = stack->head;
    stack->head = newNode;
    stack->size++;
}

// -----------------------------------------------------------------------------
// Function: top
// Purpose:  Returns the top element of the stack without removing it
// -----------------------------------------------------------------------------
Item top(Stack *stack) {
    if (isStackEmpty(stack)) {
        fprintf(stderr, "Error: Attempt to access top of an empty stack.\n");
        exit(EXIT_FAILURE);  // or return a sentinel value
    }
    return stack->head->elem;
}

// -----------------------------------------------------------------------------
// Function: pop
// Purpose:  Removes the top element of the stack
// -----------------------------------------------------------------------------
void pop(Stack *stack) {
    if (isStackEmpty(stack)) {
        fprintf(stderr, "Error: Cannot pop from an empty stack.\n");
        return;
    }

    StackNode* temp = stack->head;
    stack->head = stack->head->next;
    stack->size--;

    free(temp);
}

// -----------------------------------------------------------------------------
// Function: destroyStack
// Purpose:  Frees all memory used by the stack
// -----------------------------------------------------------------------------
void destroyStack(Stack *stack) {
    if (stack == NULL) return;

    StackNode* current = stack->head;
    while (current != NULL) {
        StackNode* temp = current;
        current = current->next;
        free(temp);
    }

    free(stack);  // Finally, free the stack structure itself
}

#endif /* STACK_H_ */
