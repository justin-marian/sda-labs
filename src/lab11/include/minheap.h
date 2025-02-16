#ifndef __HEAP_H__
#define __HEAP_H__

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef int Item;

/**
 * Structure representing an item in the priority queue.
 * Each item contains:
 * - `content` : the actual data (of type `Item`).
 * - `prior` : priority of the item (lower value = higher priority).
 */
typedef struct {
  Item content;
  int prior;
} ItemType;

/**
 * Structure representing a MinHeap-based Priority Queue.
 * - `capacity`: Maximum capacity of the heap.
 * - `size`: Current number of elements.
 * - `elem`: Array storing elements of type `ItemType`.
 */
typedef struct heap {
  long int capacity;
  long int size;
  ItemType *elem;
} PriQueue, *APriQueue;

/* ========================== FUNCTION DECLARATIONS ========================= */

/* Creates a new priority queue with the given initial capacity. */
APriQueue makeQueue(int capacity);

/* Returns index of left child of node at index i. */
int getLeftChild(int i);

/* Returns index of right child of node at index i. */
int getRightChild(int i);

/* Returns index of parent of node at index i. */
int getParent(int i);

/* Maintains the heap property by moving a node up if needed. */
void siftUp(APriQueue h, int idx);

/* Inserts a new element into the priority queue. */
void insert(APriQueue h, ItemType x);

/* Retrieves the minimum element from the priority queue (without removing it).
 */
ItemType getMin(APriQueue h);

/* Maintains the heap property by moving a node down if needed. */
void siftDown(APriQueue h, int idx);

/* Removes and returns the minimum element from the priority queue. */
ItemType removeMin(APriQueue h);

/* Frees all memory allocated for the priority queue. */
void freeQueue(APriQueue h);

/* ========================================================================== */

APriQueue makeQueue(int capacity) {
  if (capacity <= 0) {
    fprintf(stderr, "Error: Capacity must be greater than zero.\n");
    return NULL;
  }

  APriQueue h = (APriQueue)malloc(sizeof(PriQueue));
  if (!h) {
    fprintf(stderr, "Error: Memory allocation failed for priority queue.\n");
    return NULL;
  }

  h->elem = (ItemType *)malloc(capacity * sizeof(ItemType));
  if (!h->elem) {
    fprintf(stderr, "Error: Memory allocation failed for heap elements.\n");
    free(h);
    return NULL;
  }

  h->capacity = capacity;
  h->size = 0;
  return h;
}

int getLeftChild(int i) { return 2 * i + 1; }
int getRightChild(int i) { return 2 * i + 2; }
int getParent(int i) { return (i - 1) / 2; }

void siftUp(APriQueue h, int idx) {
  int parent = getParent(idx);

  while (parent >= 0 && h->elem[parent].prior > h->elem[idx].prior) {
    ItemType aux = h->elem[parent];
    h->elem[parent] = h->elem[idx];
    h->elem[idx] = aux;

    idx = parent;
    parent = getParent(idx);
  }
}

void insert(APriQueue h, ItemType x) {
  if (!h) {
    fprintf(stderr, "Error: Priority queue is NULL.\n");
    return;
  }

  if (h->size == h->capacity) {
    h->capacity *= 2;
    ItemType *newElem =
        (ItemType *)realloc(h->elem, h->capacity * sizeof(ItemType));
    if (!newElem) {
      fprintf(stderr,
              "Error: Memory allocation failed during heap expansion.\n");
      return;
    }
    h->elem = newElem;
  }

  h->elem[h->size] = x;
  h->size++;
  siftUp(h, h->size - 1);
}

ItemType getMin(APriQueue h) {
  if (!h || h->size == 0) {
    fprintf(stderr, "Error: Priority queue is empty.\n");
    return (ItemType){0, 0};
  }
  return h->elem[0];
}

void siftDown(APriQueue h, int idx) {
  int leftChild = getLeftChild(idx);
  int rightChild = getRightChild(idx);
  int smallest = idx;

  if (leftChild < h->size &&
      h->elem[leftChild].prior < h->elem[smallest].prior) {
    smallest = leftChild;
  }

  if (rightChild < h->size &&
      h->elem[rightChild].prior < h->elem[smallest].prior) {
    smallest = rightChild;
  }

  if (smallest != idx) {
    ItemType aux = h->elem[smallest];
    h->elem[smallest] = h->elem[idx];
    h->elem[idx] = aux;

    siftDown(h, smallest);
  }
}

ItemType removeMin(APriQueue h) {
  if (!h || h->size == 0) {
    fprintf(stderr, "Error: Cannot remove from empty priority queue.\n");
    return (ItemType){0, 0};
  }

  ItemType min = getMin(h);
  ItemType last = h->elem[h->size - 1];

  h->size--;
  h->elem[0] = last;
  siftDown(h, 0);

  return min;
}

void freeQueue(APriQueue h) {
  if (!h)
    return;
  free(h->elem);
  free(h);
}

#endif // __HEAP_H__