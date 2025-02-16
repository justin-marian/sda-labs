#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct QueueNode {
    Item elem;
    struct QueueNode *next;
} QueueNode;

typedef struct Queue {
    QueueNode *front;
    QueueNode *rear;
    long size;
} Queue;

// -----------------------------------------------------------------------------
// Function: createQueue
// Purpose:  Creates a new empty queue
// -----------------------------------------------------------------------------
Queue* createQueue(void) {
    Queue* q = (Queue*) malloc(sizeof(Queue));
    if (q == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for queue.\n");
        exit(EXIT_FAILURE);
    }

    q->size = 0;
    q->front = q->rear = NULL;
    return q;
}

// -----------------------------------------------------------------------------
// Function: isQueueEmpty
// Purpose:  Checks if the queue is empty
// -----------------------------------------------------------------------------
int isQueueEmpty(Queue *q) {
    return (q == NULL || q->front == NULL);
}

// -----------------------------------------------------------------------------
// Function: enqueue
// Purpose:  Adds an element to the end of the queue
// -----------------------------------------------------------------------------
void enqueue(Queue *q, Item elem) {
    if (q == NULL) {
        fprintf(stderr, "Error: Cannot enqueue into a NULL queue.\n");
        return;
    }

    QueueNode* newNode = (QueueNode*) malloc(sizeof(QueueNode));
    if (newNode == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for enqueue.\n");
        exit(EXIT_FAILURE);
    }

    newNode->elem = elem;
    newNode->next = NULL;
    q->size++;

    if (isQueueEmpty(q)) {
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

// -----------------------------------------------------------------------------
// Function: front
// Purpose:  Returns the front element of the queue without removing it
// -----------------------------------------------------------------------------
Item front(Queue* q) {
    if (isQueueEmpty(q)) {
        fprintf(stderr, "Error: Attempt to get front of an empty queue.\n");
        exit(EXIT_FAILURE);
    }
    return q->front->elem;
}

// -----------------------------------------------------------------------------
// Function: dequeue
// Purpose:  Removes the front element of the queue
// -----------------------------------------------------------------------------
void dequeue(Queue* q) {
    if (isQueueEmpty(q)) {
        fprintf(stderr, "Error: Cannot dequeue from an empty queue.\n");
        return;
    }

    QueueNode* temp = q->front;
    q->front = q->front->next;
    q->size--;

    if (q->front == NULL) {
        q->rear = NULL;
    }

    free(temp);
}

// -----------------------------------------------------------------------------
// Function: destroyQueue
// Purpose:  Frees all memory used by the queue
// -----------------------------------------------------------------------------
void destroyQueue(Queue *q) {
    if (q == NULL) return;

    QueueNode* current = q->front;
    while (current != NULL) {
        QueueNode* temp = current;
        current = current->next;
        free(temp);
    }

    free(q);
}

#endif /* QUEUE_H_ */
