#include <stdio.h>
#include <stdlib.h>

typedef int Item;

#include "include/Queue.h"

// -----------------------------------------------------------------------------
// Assertion Macros for Test Cases
// -----------------------------------------------------------------------------
#define ASSERT(cond, msg) \
	if (!(cond)) 		  \
	{ 					  \
		failed(msg); 	  \
		return 0; 		  \
	}

/**
 * Prints a success message for passed tests.
 */
void passed(char* s, float score) {
    printf("✅ Test %s passed successfully!\n====> Points: %.2f\n", s, score);
}

/**
 * Prints a failure message for failed tests.
 */
void failed(char* s) {
    printf("🔥Test %s FAILED!\n", s);
}

// -----------------------------------------------------------------------------
// Test Structure
// -----------------------------------------------------------------------------
typedef struct Test {
    int (*testFunction)(void**, float);
    float score;
} Test;

// -----------------------------------------------------------------------------
// Test for Queue Creation
// -----------------------------------------------------------------------------
int testCreate(void** queue, float score) {
    ASSERT((*queue) == NULL, "Create-01: Queue should be NULL before creation");

    *queue = (void*) createQueue();

    ASSERT((*((Queue**)queue)) != NULL, "Create-02: Queue should be created");
    ASSERT((*((Queue**)queue))->front == NULL, "Create-03: Front should be NULL initially");
    ASSERT((*((Queue**)queue))->rear == NULL, "Create-04: Rear should be NULL initially");
    ASSERT((*((Queue**)queue))->size == 0, "Create-05: Size should be 0 initially");

    printf("=> ");
    passed("Create", score);
    return 1;
}

// -----------------------------------------------------------------------------
// Test for Checking if Queue is Empty
// -----------------------------------------------------------------------------
int testIsEmpty(void** queue, float score) {
    ASSERT((*queue) != NULL, "IsEmpty-01: Queue should be created");

    ASSERT(isQueueEmpty(*queue) == 1, "IsEmpty-02: Queue should be empty initially");

    // Simulate adding an item without enqueue()
    QueueNode aNode = {2, NULL};
    (*((Queue**)queue))->rear = &aNode;
    (*((Queue**)queue))->front = &aNode;

    ASSERT(isQueueEmpty(*queue) == 0, "IsEmpty-03: Queue should not be empty after adding an item");

    // Reset queue state
    (*((Queue**)queue))->front = (*((Queue**)queue))->rear = NULL;
    ASSERT((*((Queue**)queue))->size == 0, "IsEmpty-04: Size should still be 0");

    printf("=> ");
    passed("IsQueueEmpty", score);
    return 1;
}

// -----------------------------------------------------------------------------
// Test for Enqueue
// -----------------------------------------------------------------------------
int testEnqueue(void** queue, float score) {
    ASSERT((*queue) != NULL, "Enqueue-01: Queue should be created");

    ASSERT((*((Queue**)queue))->front == NULL, "Enqueue-02: Front should be NULL before enqueue");
    ASSERT((*((Queue**)queue))->rear == NULL, "Enqueue-03: Rear should be NULL before enqueue");
    ASSERT((*((Queue**)queue))->size == 0, "Enqueue-04: Size should be 0 before enqueue");

    enqueue(*queue, 1);
    ASSERT((*((Queue**)queue))->size == 1, "Enqueue-07: Size should be 1 after enqueue");
    ASSERT((*((Queue**)queue))->front->elem == 1, "Enqueue-08: Front should be 1");
    ASSERT((*((Queue**)queue))->rear->elem == 1, "Enqueue-09: Rear should be 1");

    enqueue(*queue, 2);
    ASSERT((*((Queue**)queue))->size == 2, "Enqueue-14: Size should be 2 after second enqueue");
    ASSERT((*((Queue**)queue))->front->elem == 1, "Enqueue-17: Front should still be 1");
    ASSERT((*((Queue**)queue))->rear->elem == 2, "Enqueue-18: Rear should now be 2");

    printf("=> ");
    passed("Enqueue", score);
    return 1;
}

// -----------------------------------------------------------------------------
// Test for Front Element
// -----------------------------------------------------------------------------
int testFront(void** queue, float score) {
    ASSERT((*queue) != NULL, "Front-01: Queue should be created");

    enqueue(*queue, 6);
    ASSERT((*((Queue**)queue))->front->elem == 1, "Front-02: Front should be 1");
    ASSERT((*((Queue**)queue))->rear->elem == 6, "Front-03: Rear should be 6");

    printf("=> ");
    passed("Front", score);
    return 1;
}

// -----------------------------------------------------------------------------
// Test for Dequeue
// -----------------------------------------------------------------------------
int testDequeue(void** queue, float score) {
    ASSERT((*queue) != NULL, "Dequeue-01: Queue should be created");

    int initialSize = (*((Queue**)queue))->size;

    dequeue(*queue);
    ASSERT((*((Queue**)queue))->size == initialSize - 1, "Dequeue-03: Size should decrease after dequeue");

    printf("=> ");
    passed("Dequeue", score);
    return 1;
}

// -----------------------------------------------------------------------------
// Test for Queue Destruction
// -----------------------------------------------------------------------------
int testDestroy(void** queue, float score) {
    ASSERT((*queue) != NULL, "Destroy-01: Queue should exist before destruction");

    destroyQueue(*queue);
    *queue = NULL;

    printf("<========================================>\n");
    printf("Destroy will be checked with valgrind!\n====> Points: %.2f.\n", score);
    return 1;
}

// -----------------------------------------------------------------------------
// Main Function: Runs All Tests
// -----------------------------------------------------------------------------
int main() {
    Queue* queue = NULL;

    // Define the tests
    Test tests[] = {
        { &testCreate, 0.03 },
        { &testIsEmpty, 0.02 },
        { &testEnqueue, 0.1 },
        { &testFront, 0.05 },
        { &testDequeue, 0.1 },
        { &testDestroy, 0.1 },
    };

    float totalScore = 0.0f, maxScore = 0.0f;
    long testsNo = sizeof(tests) / sizeof(Test);
    long testIdx;

    // Run all tests
    for (testIdx = 0; testIdx < testsNo; testIdx++) {
        float score = tests[testIdx].score;
        if (tests[testIdx].testFunction(((void**) &queue), score)) {
            totalScore += score;
        }
        maxScore += score;
    }

    printf("\nTotal Score: %.2f / %.2f\n\n", totalScore, maxScore);
    return 0;
}
