#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Maximum number of characters that can be read
 * in one go from the keyboard.
 */
#define MAX_INPUT_LEN 255

typedef char Item;

#include "include/DoubleLinkedList.h"

// -----------------------------------------------------------------------------
// Assertion Macros for Test Cases
// -----------------------------------------------------------------------------
#define ASSERT(cond, msg) if (!(cond)) { failed(msg); return 0; }

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
// Test Cases
// -----------------------------------------------------------------------------

/**
 * Test for creating an empty list.
 */
int testCreate(void** list, float score) {
    ASSERT((*list) == NULL, "Create-01");

    *list = (void*) createList();

    ASSERT((*((List**)list)) != NULL, "Create-02");
    ASSERT((*((List**)list))->first == NULL, "Create-03");
    ASSERT((*((List**)list))->last == NULL, "Create-04");

    printf("=> ");
    passed("Create", score);
    return 1;
}

/**
 * Test for checking if a list is empty.
 */
int testIsEmpty(void** list, float score) {
    ASSERT((*list) != NULL, "IsEmpty-01");

    ASSERT(isEmpty(*((List**)list)) == 1, "IsEmpty-02");

    ListNode aNode = {'x', NULL, NULL};
    (*((List**)list))->first = (*((List**)list))->last = &aNode;

    ASSERT(isEmpty(*((List**)list)) == 0, "IsEmpty-03");

    (*((List**)list))->first = (*((List**)list))->last = NULL;
    ASSERT(isEmpty(*((List**)list)) == 1, "IsEmpty-04");

    printf("=> ");
    passed("IsEmpty", score);
    return 1;
}

/**
 * Test for checking if an element exists in the list.
 */
int testContains(void** list, float score) {
    ASSERT((*list) != NULL, "Contains-01");

    ASSERT(contains((*((List**)list)), 'x') == 0, "Contains-02");
    ASSERT(contains((*((List**)list)), 'y') == 0, "Contains-03");
    ASSERT(contains((*((List**)list)), 'z') == 0, "Contains-04");

    ListNode nodes[] = {
        {'x', NULL, NULL},
        {'y', NULL, NULL},
        {'z', NULL, NULL}
    };

    (*((List**)list))->first = nodes;
    (*((List**)list))->last = (nodes + 2);

    nodes->next = (nodes + 1);
    (nodes + 2)->prev = (nodes + 1);
    (nodes + 1)->next = (nodes + 2);
    (nodes + 1)->prev = nodes;

    ASSERT(contains((*((List**)list)), 'x') == 1, "Contains-06");
    ASSERT(contains((*((List**)list)), 'y') == 1, "Contains-07");
    ASSERT(contains((*((List**)list)), 'z') == 1, "Contains-08");

    (*((List**)list))->first = (*((List**)list))->last = NULL;

    printf("=> ");
    passed("Contains", score);
    return 1;
}

/**
 * Test for inserting elements at different positions.
 */
int testInsert(void** list, float score) {
    ASSERT((*list) != NULL, "Insert-01");

    insertAt((*((List**)list)), 'x', 0);
    ASSERT(isEmpty(*((List**)list)) == 0, "Insert-02");
    ASSERT((*((List**)list))->first->elem == 'x', "Insert-03");
    ASSERT((*((List**)list))->last->elem == 'x', "Insert-04");

    insertAt((*((List**)list)), 'y', 0);
    ASSERT((*((List**)list))->first->elem == 'y', "Insert-05");
    ASSERT((*((List**)list))->last->elem == 'x', "Insert-06");

    insertAt((*((List**)list)), 'z', 2);
    ASSERT((*((List**)list))->last->elem == 'z', "Insert-07");

    printf("=> ");
    passed("Insert", score);
    return 1;
}

/**
 * Test for deleting a single occurrence of an element.
 */
int testDeleteOnce(void** list, float score) {
    ASSERT((*list) != NULL, "DeleteOnce-01");

    deleteOnce((*((List**)list)), 'x');
    ASSERT(contains((*((List**)list)), 'x') == 0, "DeleteOnce-02");

    deleteOnce((*((List**)list)), 'y');
    ASSERT((*((List**)list))->first->elem == 'z', "DeleteOnce-03");

    deleteOnce((*((List**)list)), 'z');
    ASSERT(isEmpty(*((List**)list)) == 1, "DeleteOnce-04");

    printf("=> ");
    passed("DeleteOnce", score);
    return 1;
}

/**
 * Test for calculating list length.
 */
int testLength(void** list, float score) {
    ASSERT((*list) != NULL, "Length-01");

    ASSERT(length(*((List**)list)) == 0, "Length-02");

    insertAt((*((List**)list)), 'x', 0);
    insertAt((*((List**)list)), 'y', 1);
    insertAt((*((List**)list)), 'z', 2);

    ASSERT(length(*((List**)list)) == 3, "Length-03");

    printf("=> ");
    passed("Length", score);
    return 1;
}

/**
 * Test for destroying a list.
 */
int testDestroy(void** list, float score) {
    *list = destroyList(*((List**)list));
    printf("<========================================>\n");
    printf("Destroy will be checked with valgrind!\n====> Points: %.2f.\n", score);
    return 1;
}

// -----------------------------------------------------------------------------
// Utility Functions
// -----------------------------------------------------------------------------

/**
 * Prints the list from head to tail.
 */
void printList(List *list) {
    ListNode* iterator = list->first;
    printf("[");
    while (iterator != list->last) {
        printf("%c, ", iterator->elem);
        iterator = iterator->next;
    }
    printf("%c]", list->last->elem);
}

/**
 * Prints the list from tail to head (reverse order).
 */
void printListReverse(List* list) {
    ListNode* iterator = list->last;
    printf("[");
    while (iterator != list->first) {
        printf("%c, ", iterator->elem);
        iterator = iterator->prev;
    }
    printf("%c]", list->first->elem);
}

// -----------------------------------------------------------------------------
// Main Function
// -----------------------------------------------------------------------------
int main() {
    List *list = NULL;

    Test tests[] = {
        { &testCreate, 0.05 },
        { &testIsEmpty, 0.05 },
        { &testContains, 0.1 },
        { &testInsert, 0.2 },
        { &testDeleteOnce, 0.2 },
        { &testLength, 0.1 },
        { &testDestroy, 0.1 },
    };

    float totalScore = 0.0f, maxScore = 0.0f;
    long testsNo = sizeof(tests) / sizeof(Test);

    for (long testIdx = 0; testIdx < testsNo; testIdx++) {
        if (tests[testIdx].testFunction(((void**) &list), tests[testIdx].score)) {
            totalScore += tests[testIdx].score;
        }
        maxScore += tests[testIdx].score;
    }

    printf("\nTotal Score: %.2f / %.2f\n\n", totalScore, maxScore);
    return 0;
}
