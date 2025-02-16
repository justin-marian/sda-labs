#include <stdio.h>
#include <stdlib.h>

#include "include/queue.h"

/**
 * Initializes a new node with the given data.
 * Returns the newly created node or NULL if allocation fails.
 */
Node *initNode(T data) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (!node) {
        fprintf(stderr, "Error: Memory allocation failed for queue node.\n");
        return NULL;
    }
    node->data = data;
    node->next = NULL;
    return node;
}

/**
 * Frees a given node and returns NULL.
 */
Node *freeNode(Node *node) {
    if (node) free(node);
    return NULL;
}

/**
 * Initializes a new queue with the given data.
 * Returns the newly created queue or NULL if allocation fails.
 */
Queue initQueue(T data) {
    Queue queue = (Queue)malloc(sizeof(struct queue));
    if (!queue) {
        fprintf(stderr, "Error: Memory allocation failed for queue.\n");
        return NULL;
    }
    queue->head = queue->tail = initNode(data);
    if (!queue->head) {
        free(queue);
        return NULL;
    }
    queue->size = 1;
    return queue;
}

/**
 * Adds a new element to the end of the queue.
 * Returns the updated queue.
 */
Queue enqueue(Queue queue, T data) {
    Node *node = initNode(data);
    if (!node) return queue;

    if (isEmptyQueue(queue)) {
        if (queue == NULL)
            return initQueue(data);
        free(queue);
        return initQueue(data);
    }
    
    queue->tail->next = node;
    queue->tail = node;
    queue->size++;
    return queue;
}

/**
 * Removes the front element from the queue.
 * Returns the updated queue.
 */
Queue dequeue(Queue queue) {
    if (isEmptyQueue(queue)) {
        fprintf(stderr, "Warning: Trying to dequeue from an empty queue.\n");
        return queue;
    }

    Node *tmp = queue->head;
    queue->head = queue->head->next;
    tmp = freeNode(tmp);
    queue->size--;

    if (queue->size == 0) {
        queue->tail = NULL;
    }

    return queue;
}

/**
 * Returns the front element of the queue without removing it.
 * Returns -1 if the queue is empty.
 */
T first(Queue queue) {
    if (!isEmptyQueue(queue)) {
        return queue->head->data;
    } else {
        fprintf(stderr, "Warning: Trying to access first element of an empty queue.\n");
        return -1;
    }
}

/**
 * Checks if the queue is empty.
 * Returns 1 if empty, 0 otherwise.
 */
int isEmptyQueue(Queue queue) {
    return (queue == NULL || queue->head == NULL || queue->size == 0);
}

/**
 * Frees all elements in the queue and returns NULL.
 */
Queue freeQueue(Queue queue) {
    while (!isEmptyQueue(queue)) {
        queue = dequeue(queue);
    }
    if (queue)
        free(queue);
    return NULL;
}
