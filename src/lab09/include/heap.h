#ifndef __HEAP_H__
#define __HEAP_H__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    void *elem;
    int prior;
} HeapNode, *PHeapNode;

typedef struct {
    long int capacity;
    long int size;
    PHeapNode *nodes;
} Heap, *PHeap;

// ---------------- Heap Functions ----------------

PHeap makeHeap(int capacity) {
    if (capacity <= 0) {
        fprintf(stderr, "Error: Invalid heap capacity.\n");
        return NULL;
    }

    PHeap heap = (PHeap)malloc(sizeof(Heap));
    if (!heap) {
        fprintf(stderr, "Error: Heap allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    heap->capacity = capacity;
    heap->size = 0;
    heap->nodes = (PHeapNode*)malloc(capacity * sizeof(PHeapNode));

    if (!heap->nodes) {
        fprintf(stderr, "Error: Heap nodes allocation failed.\n");
        free(heap);
        exit(EXIT_FAILURE);
    }

    return heap;
}

int getLeftChild(int i) { return 2 * i + 1; }
int getRightChild(int i) { return 2 * i + 2; }
int getParent(int i) { return (i - 1) / 2; }

void swap(PHeapNode *a, PHeapNode *b) {
    PHeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void siftUp(PHeap h, int idx) {
    int parent = getParent(idx);

    while (idx > 0 && h->nodes[parent]->prior > h->nodes[idx]->prior) {
        swap(&h->nodes[parent], &h->nodes[idx]);
        idx = parent;
        parent = getParent(idx);
    }
}

void insert(PHeap h, void *elem, int prior) {
    if (!h || !elem) {
        fprintf(stderr, "Error: Heap or element is NULL.\n");
        return;
    }

    if (h->size == h->capacity) {
        h->capacity *= 2;
        h->nodes = (PHeapNode*)realloc(h->nodes, h->capacity * sizeof(PHeapNode));
        if (!h->nodes) {
            fprintf(stderr, "Error: Heap resize failed.\n");
            exit(EXIT_FAILURE);
        }
    }

    PHeapNode newNode = (PHeapNode)malloc(sizeof(HeapNode));
    if (!newNode) {
        fprintf(stderr, "Error: HeapNode allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    newNode->elem = elem;
    newNode->prior = prior;

    h->nodes[h->size] = newNode;
    siftUp(h, h->size);
    h->size++;
}

PHeapNode getMin(PHeap h) {
    return (h && h->size > 0) ? h->nodes[0] : NULL;
}

void siftDown(PHeap h, int idx) {
    int leftChild = getLeftChild(idx);
    int rightChild = getRightChild(idx);
    int smallest = idx;

    if (leftChild < h->size && h->nodes[leftChild]->prior < h->nodes[smallest]->prior) {
        smallest = leftChild;
    }

    if (rightChild < h->size && h->nodes[rightChild]->prior < h->nodes[smallest]->prior) {
        smallest = rightChild;
    }

    if (smallest != idx) {
        swap(&h->nodes[smallest], &h->nodes[idx]);
        siftDown(h, smallest);
    }
}

PHeapNode removeMin(PHeap h) {
    if (!h || h->size == 0) {
        fprintf(stderr, "Error: Cannot remove from empty heap.\n");
        return NULL;
    }

    PHeapNode minNode = h->nodes[0];
    h->size--;

    if (h->size > 0) {
        h->nodes[0] = h->nodes[h->size];
        siftDown(h, 0);
    }

    return minNode;
}

void freeHeap(PHeap h) {
    if (!h) return;

    for (int i = 0; i < h->size; i++) {
        free(h->nodes[i]);
    }
    
    free(h->nodes);
    free(h);
}

#endif /* __HEAP_H__ */
