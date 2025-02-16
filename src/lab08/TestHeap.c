#include <stdio.h>
#include <stdlib.h>

typedef unsigned char Item;

#include "include/Heap.h"

ItemType elements[] = {{4, 4}, {2, 2}, {8, 8}, {7, 7}};
int len = 4;

// -----------------------------------------------------------------------------

// Macros for Testing
#define ASSERT(cond, msg) \
    if (!(cond)) { failed(msg); return 0; }

void passed(char *s, float score) {
    printf("✅ Test %s passed successfully! Score: %.2f\n", s, score);
}

void failed(char *s) {
    printf("❌ Test %s FAILED!\n", s);
}

void swap(ItemType *a, ItemType *b) {
    ItemType temp = *a;
    *a = *b;
    *b = temp;
}

// -----------------------------------------------------------------------------
// Test `makeQueue`
int testMakeQueue(PriQueue **pq, float score) {
    *pq = makeQueue(len / 2);
    ASSERT((*pq) != NULL, "MakeQueue-01");
    ASSERT((*pq)->elem != NULL, "MakeQueue-02");
    ASSERT((*pq)->maxHeapSize == len / 2, "MakeQueue-03");
    ASSERT((*pq)->size == 0, "MakeQueue-04");

    passed("MakeQueue", score);
    return 1;
}

// Test `getParent`
int testGetParent(PriQueue **pq, float score) {
    ASSERT(getParent(2) == 0, "GetParent-01");
    ASSERT(getParent(9) == 4, "GetParent-02");
    ASSERT(getParent(4) == 1, "GetParent-03");

    passed("GetParent", score);
    return 1;
}

// Test `getLeftChild`
int testGetLeftChild(PriQueue **pq, float score) {
    ASSERT(getLeftChild(0) == 1, "GetLeftChild-01");
    ASSERT(getLeftChild(2) == 5, "GetLeftChild-02");
    ASSERT(getLeftChild(3) == 7, "GetLeftChild-03");
    ASSERT(getLeftChild(6) == 13, "GetLeftChild-04");

    passed("GetLeftChild", score);
    return 1;
}

// Test `getRightChild`
int testGetRightChild(PriQueue **pq, float score) {
    ASSERT(getRightChild(0) == 2, "GetRightChild-01");
    ASSERT(getRightChild(2) == 6, "GetRightChild-02");
    ASSERT(getRightChild(3) == 8, "GetRightChild-03");
    ASSERT(getRightChild(6) == 14, "GetRightChild-04");

    passed("GetRightChild", score);
    return 1;
}

// Test `siftUp`
int testSiftUp(PriQueue **pq, float score) {
    (*pq)->elem[0].prior = 4;
    siftUp(*pq, 0);
    ASSERT((*pq)->elem[0].prior == 4, "ShiftUp-01");

    (*pq)->elem[1].prior = 2;
    siftUp(*pq, 1);
    ASSERT((*pq)->elem[0].prior == 4, "ShiftUp-02");

    passed("SiftUp", score);
    return 1;
}

// Test `insert`
int testInsert(PriQueue **pq, float score) {
    for (int i = 0; i < len; i++) {
        insert(*pq, elements[i]);
    }

    ASSERT((*pq)->size == 4, "Insert-01");
    ASSERT((*pq)->elem[0].prior == 8, "Insert-02");
    ASSERT((*pq)->elem[1].prior == 7, "Insert-03");
    ASSERT((*pq)->elem[2].prior == 4, "Insert-04");
    ASSERT((*pq)->elem[3].prior == 2, "Insert-05");

    passed("Insert", score);
    return 1;
}

// Test `getMax`
int testGetMax(PriQueue **pq, float score) {
    ASSERT(getMax(*pq).prior == 8, "GetMax-01");

    passed("GetMax", score);
    return 1;
}

// Test `siftDown`
int testSiftDown(PriQueue **pq, float score) {
    swap(&(*pq)->elem[0], &(*pq)->elem[(*pq)->size - 1]);
    siftDown(*pq, 0);
    ASSERT(getMax(*pq).prior == 7, "ShiftDown-01");

    siftUp(*pq, (*pq)->size - 3);
    ASSERT((*pq)->elem[0].prior == 8, "ShiftDown-02");

    passed("SiftDown", score);
    return 1;
}

// Test `removeMax`
int testRemoveMax(PriQueue **pq, float score) {
    removeMax(*pq);
    ASSERT((*pq)->size == 3, "RemoveMax-01");
    ASSERT(getMax(*pq).prior == 7, "RemoveMax-02");

    removeMax(*pq);
    ASSERT((*pq)->size == 2, "RemoveMax-03");
    ASSERT(getMax(*pq).prior == 4, "RemoveMax-04");

    removeMax(*pq);
    ASSERT((*pq)->size == 1, "RemoveMax-05");
    ASSERT(getMax(*pq).prior == 2, "RemoveMax-06");

    removeMax(*pq);
    ASSERT((*pq)->size == 0, "RemoveMax-07");

    passed("RemoveMax", score);
    return 1;
}

// Test `freeQueue`
int testFreeQueue(PriQueue **pq, float score) {
    freeQueue(*pq);
    *pq = NULL;
    printf("✅ FreeQueue test: *Memory will be checked with Valgrind* Score: %.2f\n", score);
    return 1;
}

// -----------------------------------------------------------------------------
// 🚀 **Test Suite**
typedef struct {
    int (*testFunction)(PriQueue **pq, float);
    float score;
} Test;

int main(int argc, char *argv[]) {
    Test tests[] = {
        { testMakeQueue, 0.1 },
        { testGetParent, 0.05 },
        { testGetLeftChild, 0.05 },
        { testGetRightChild, 0.05 },
        { testSiftUp, 0.2 },
        { testInsert, 0.1 },
        { testGetMax, 0.05 },
        { testSiftDown, 0.2 },
        { testRemoveMax, 0.1 },
        { testFreeQueue, 0.1 },
    };

    float totalScore = 0.0f, maxScore = 0.0f;
    long testsNo = sizeof(tests) / sizeof(Test);
    PriQueue *pq = NULL;

    for (long testIdx = 0; testIdx < testsNo; testIdx++) {
        float score = tests[testIdx].score;
        if ((*(tests[testIdx].testFunction))(&pq, score)) {
            totalScore += score;
        }
        maxScore += score;
    }

    printf("\nTotal Score: %.2f / %.2f\n", totalScore, maxScore);
    return 0;
}
