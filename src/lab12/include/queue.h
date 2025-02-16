#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stdio.h>
#include <stdlib.h>

/* ========================== STRUCTURES ========================== */

typedef int T;

/**
 * Structure representing a **node** in the queue.
 */
typedef struct node {
    T data;
    struct node *next;
} Node;

/**
 * Structure representing a **queue** (FIFO).
 * - `head`: Points to the front of the queue.
 * - `tail`: Points to the end of the queue.
 * - `size`: Number of elements in the queue.
 */
typedef struct queue {
    Node *head, *tail;
    int size;
} *Queue;

/* ========================== FUNCTION DECLARATIONS ========================== */

/* Creates a new queue and adds `data` as the first element. */
Queue initQueue(T data);

/* Creates a new node with `data`. */
Node *initNode(T data);

/* Adds an element to the queue. */
Queue enqueue(Queue queue, T data);

/* Removes the first element from the queue. */
Queue dequeue(Queue queue);

/* Returns the value of the first element (without removing it). */
T first(Queue queue);

/* Checks if the queue is empty. */
int isEmptyQueue(Queue queue);

/* Frees memory allocated for a node. */
Node *freeNode(Node *node);

/* Frees the entire queue and its elements. */
Queue freeQueue(Queue queue);

/* ========================================================================== */

#endif /* __QUEUE_H__ */
