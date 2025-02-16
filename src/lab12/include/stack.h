#ifndef __STACK_H__
#define __STACK_H__

#include <stdio.h>
#include <stdlib.h>

/* ===================== STRUCTURES ===================== */

typedef int E;

/**
 * Structure representing a stack node.
 * Each node stores:
 * - `data`: The element stored in the stack.
 * - `next`: Pointer to the next node.
 */
typedef struct stack {
	E data;
	struct stack *next;
} *Stack;

/* ===================== FUNCTION DECLARATIONS ===================== */

/**
 * Initializes a new stack and adds a value to it.
 * @param data Value to be stored in the new stack.
 * @return Pointer to the newly created stack.
 */
Stack initStack(E data);

/**
 * Pushes a new element onto the stack.
 * @param s Stack pointer.
 * @param data Value to be added.
 * @return Updated stack pointer with the new top element.
 */
Stack push(Stack s, E data);

/**
 * Removes the top element from the stack.
 * @param s Stack pointer.
 * @return Updated stack pointer after removal.
 */
Stack pop(Stack s);

/**
 * Returns the top element from the stack without removing it.
 * @param s Stack pointer.
 * @return The top element, or -1 if the stack is empty.
 */
E top(Stack s);

/**
 * Checks if the stack is empty.
 * @param s Stack pointer.
 * @return 1 if the stack is empty, 0 otherwise.
 */
int isEmptyStack(Stack s);

/**
 * Frees the memory allocated for the entire stack.
 * @param s Stack pointer.
 * @return NULL after freeing all nodes.
 */
Stack freeStack(Stack s);

/* ========================================================================== */

#endif /* __STACK_H__ */
