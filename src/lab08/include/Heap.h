#ifndef __HEAP_H__
#define __HEAP_H__

#include <stdlib.h>
#include <math.h>

typedef struct {
    int prior;
    Item data;
} ItemType;

typedef struct heap {
    long maxHeapSize;
    long size;
    ItemType *elem;
} PriQueue, *APriQueue;

// Create a new priority queue
PriQueue* makeQueue(int maxHeapSize) {
    PriQueue* pq = (PriQueue*) malloc(sizeof(PriQueue));
    if (!pq) return NULL;

    pq->size = 0;
    pq->maxHeapSize = maxHeapSize;
    pq->elem = (ItemType*) malloc(pq->maxHeapSize * sizeof(ItemType));

    if (!pq->elem) {
        free(pq);
        return NULL;
    }

    return pq;
}

// Get left child index
int getLeftChild(int i) {
    return 2 * i + 1;
}

// Get right child index
int getRightChild(int i) {
    return 2 * i + 2;
}

// Get parent index (handle root case)
int getParent(int i) {
    return (i == 0) ? -1 : (i - 1) / 2;
}

// Get max element (check if empty)
ItemType getMax(APriQueue h) {
    if (h->size == 0) {
        ItemType empty = { 
			.prior = -1, 
			.data = empty.data
		};
        return empty; 
    }
    return h->elem[0];
}

// Restore heap property upwards
void siftUp(APriQueue h, int idx) {
    while (idx > 0 && h->elem[idx].prior > h->elem[getParent(idx)].prior) {
        // Swap current node with parent
        ItemType temp = h->elem[getParent(idx)];
        h->elem[getParent(idx)] = h->elem[idx];
        h->elem[idx] = temp;

        // Move to parent index
        idx = getParent(idx);
    }
}

// Insert element into the priority queue
void insert(PriQueue *h, ItemType x) {
    if (!h) return;

    // Resize if full
    if (h->size == h->maxHeapSize) {
        h->maxHeapSize *= 2;
        h->elem = (ItemType*) realloc(h->elem, h->maxHeapSize * sizeof(ItemType));
        if (!h->elem) return;
    }

    // Insert element at the end
    h->elem[h->size] = x;
    siftUp(h, h->size);
    h->size++;
}

// Restore heap property downwards
void siftDown(APriQueue h, int idx) {
    int maxIdx = idx;
    int left = getLeftChild(idx);
    int right = getRightChild(idx);

    if (left < h->size && h->elem[left].prior > h->elem[maxIdx].prior)
        maxIdx = left;

    if (right < h->size && h->elem[right].prior > h->elem[maxIdx].prior)
        maxIdx = right;

    if (idx != maxIdx) {
        // Swap elements
        ItemType temp = h->elem[maxIdx];
        h->elem[maxIdx] = h->elem[idx];
        h->elem[idx] = temp;

        // Recursively sift down
        siftDown(h, maxIdx);
    }
}

// Remove max element (handle empty case)
void removeMax(APriQueue h) {
    if (h->size == 0) return;

    h->elem[0] = h->elem[h->size - 1];
    h->size--;

    siftDown(h, 0);
}

// Free memory
void freeQueue(APriQueue h) {
    if (!h) return;
    free(h->elem);
    free(h);
}

#endif // __HEAP_H__
