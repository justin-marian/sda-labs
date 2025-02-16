#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef int T;

#include "include/SortedList.h"

// -------------------------- TESTING MACROS --------------------------

#define sd_assert(message, test) \
    do { \
        if (!(test)) { \
            printf("❌ Test failed: %s\n", message); \
            return message; \
        } \
    } while (0)

#define sd_run_test(test, score) \
    do { \
        char *message = test(); \
        tests_run++; \
        if (message) { \
            return message; \
        } else { \
            total_score += score; \
            printf("\t✔ Passed! Score: %.2lf\n", 1.0 * score); \
        } \
    } while (0)

int tests_run = 0;
float total_score = 0;

// -------------------------- UTILITY FUNCTION --------------------------

/*
    Checks if the sorted list `l` matches the expected array `vector` of size `size`.
*/
int check(TSortedList l, int *vector, int size) {
    if (l == NULL && size == 0) {
        return 1; // Empty list should match an empty array.
    }

    int i = 0;
    while (l != NULL && i < size) {
        if (l->value != vector[i++]) {
            printf("❌ Mismatch: Expected %d, Found %d at index %d\n", vector[i - 1], l->value, i - 1);
            return 0;
        }
        l = l->next;
    }

    return (l == NULL && i == size);
}

// -------------------------- TEST CASES --------------------------

/*
    Test for creating a sorted list.
*/
static char *test_create() {
    int v[1] = {5};
    TSortedList l = create(5);
    sd_assert("create - Test 1 failed", check(l, v, 1));
    l = freeTSortedList(l);

    l = create(10);
    v[0] = 10;
    sd_assert("create - Test 2 failed", check(l, v, 1));
    l = freeTSortedList(l);

    printf("✔ test_create() - All tests passed!\n");
    return 0;
}

/*
    Test for checking if a list is empty.
*/
static char *test_isEmpty() {
    TSortedList l = NULL;
    sd_assert("isEmpty - Test 1 failed", isEmpty(l));

    l = create(10);
    int v[] = {10};
    sd_assert("isEmpty - Test 2 failed", check(l, v, 1));
    l = freeTSortedList(l);

    printf("✔ test_isEmpty() - All tests passed!\n");
    return 0;
}

/*
    Comparator function for sorting arrays.
*/
int cmp(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

static char *test_insert() {
    int *v, size, i;
    TSortedList l = NULL;

    // Test with 5 elements
    size = 5;
    v = (int*) malloc(size * sizeof(int));
    for (i = 0; i < size; i++) {
        v[i] = rand() % 100;
        l = insert(l, v[i]);
    }
    qsort(v, size, sizeof(int), cmp);
    sd_assert("insert - Test 1 failed", check(l, v, size));
    l = freeTSortedList(l);
    free(v);

    // Test with 15 elements
    size = 15;
    v = (int*) malloc(size * sizeof(int));
    l = NULL;
    for (i = 0; i < size; i++) {
        v[i] = rand() % 100;
        l = insert(l, v[i]);
    }
    qsort(v, size, sizeof(int), cmp);
    sd_assert("insert - Test 2 failed", check(l, v, size));
    l = freeTSortedList(l);
    free(v);

    // Test with 50 elements
    size = 50;
    v = (int*) malloc(size * sizeof(int));
    l = NULL;
    for (i = 0; i < size; i++) {
        v[i] = rand() % 100;
        l = insert(l, v[i]);
    }
    qsort(v, size, sizeof(int), cmp);
    sd_assert("insert - Test 3 failed", check(l, v, size));
    l = freeTSortedList(l);
    free(v);

    printf("insert() - All tests passed!\n");
    return 0;
}

static char *test_contains() {
    int *v, size, i;
    TSortedList l = NULL;

    // Test with 5 elements
    size = 5;
    v = (int*) malloc(size * sizeof(int));
    for (i = 0; i < size; i++) {
        v[i] = rand() % 100;
        l = insert(l, v[i]);
    }
    qsort(v, size, sizeof(int), cmp);
    sd_assert("contains - Test 1 failed", check(l, v, size) && contains(l, v[1]));
    l = freeTSortedList(l);
    free(v);

    // Test with 15 elements
    size = 15;
    v = (int*) malloc(size * sizeof(int));
    l = NULL;
    for (i = 0; i < size; i++) {
        v[i] = rand() % 100;
        l = insert(l, v[i]);
    }
    qsort(v, size, sizeof(int), cmp);
    sd_assert("contains - Test 2 failed", check(l, v, size) && !contains(l, -100));
    l = freeTSortedList(l);
    free(v);

    // Test with 50 elements
    size = 50;
    v = (int*) malloc(size * sizeof(int));
    l = NULL;
    for (i = 0; i < size; i++) {
        v[i] = rand() % 100;
        l = insert(l, v[i]);
    }
    qsort(v, size, sizeof(int), cmp);
    sd_assert("contains - Test 3 failed", check(l, v, size) && contains(l, v[22]));
    l = freeTSortedList(l);
    free(v);

    printf("contains() - All tests passed!\n");
    return 0;
}

static char *test_deleteOnce() {
    int *v, size, i, x;
    TSortedList l = NULL;

    // Test with 5 elements
    size = 5;
    v = (int*) malloc(size * sizeof(int));
    for (i = 0; i < size; i++) {
        v[i] = rand() % 100;
        l = insert(l, v[i]);
    }
    x = rand() % 100;
    l = insert(l, x);
    l = deleteOnce(l, x);
    qsort(v, size, sizeof(int), cmp);
    sd_assert("deleteOnce - Test 1 failed", check(l, v, size));
    l = freeTSortedList(l);
    free(v);

    // Test with 15 elements
    size = 15;
    v = (int*) malloc(size * sizeof(int));
    l = NULL;
    for (i = 0; i < size; i++) {
        v[i] = rand() % 100;
        l = insert(l, v[i]);
    }
    x = rand() % 100;
    l = insert(l, x);
    l = insert(l, x);
    l = deleteOnce(l, x);
    l = deleteOnce(l, x);
    qsort(v, size, sizeof(int), cmp);
    sd_assert("deleteOnce - Test 2 failed", check(l, v, size));
    l = freeTSortedList(l);
    free(v);

    // Test with 50 elements
    size = 50;
    v = (int*) malloc(size * sizeof(int));
    l = NULL;
    for (i = 0; i < size; i++) {
        v[i] = rand() % 100;
        l = insert(l, v[i]);
        x = rand() % 1000;
        l = insert(l, x);
        l = deleteOnce(l, x);
    }
    qsort(v, size, sizeof(int), cmp);
    sd_assert("deleteOnce - Test 3 failed", check(l, v, size));
    l = freeTSortedList(l);
    free(v);

    printf("deleteOnce() - All tests passed!\n");
    return 0;
}

static char *test_length() {
    int size, i, x;
    TSortedList l = NULL;

    // Test with 5 elements
    size = 5;
    for (i = 0; i < size; i++) {
        l = insert(l, rand() % 100);
    }
    sd_assert("length - Test 1 failed", length(l) == size);
    l = freeTSortedList(l);

    // Test with 15 elements
    size = 15;
    l = NULL;
    for (i = 0; i < size; i++) {
        l = insert(l, rand() % 1000);
    }
    sd_assert("length - Test 2 failed", length(l) == size);
    l = freeTSortedList(l);

    // Test with 50 elements
    size = 50;
    l = NULL;
    for (i = 0; i < size; i++) {
        x = rand() % 1000;
        l = insert(l, x);
    }
    l = deleteOnce(l, x);
    sd_assert("length - Test 3 failed", length(l) == size - 1);
    l = freeTSortedList(l);

    printf("length() - All tests passed!\n");
    return 0;
}

static char *test_getNth() {
    int *v, size, i;
    TSortedList l = NULL;

    // Test with 5 elements
    size = 5;
    v = (int*) malloc(size * sizeof(int));
    for (i = 0; i < size; i++) {
        v[i] = rand() % 100;
        l = insert(l, v[i]);
    }
    qsort(v, size, sizeof(int), cmp);
    sd_assert("getNth - Test 1 failed", getNth(l, 1) == v[0] && getNth(l, size) == v[size - 1]);
    l = freeTSortedList(l);
    free(v);

    printf("getNth() - All tests passed!\n");
    return 0;
}


// -------------------------- TEST EXECUTION --------------------------

/*
    Runs all tests.
*/
static char *all_tests() {
    sd_run_test(test_create, 0.25);
    sd_run_test(test_isEmpty, 0.25);
    sd_run_test(test_insert, 2);
    sd_run_test(test_length, 0.5);
    sd_run_test(test_contains, 0.5);
    sd_run_test(test_deleteOnce, 2);
    sd_run_test(test_getNth, 0.5);
    return 0;
}

/*
    Runs selected tests based on command-line arguments.
*/
static char *selective_tests(int argc, char **argv) {
    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "1")) sd_run_test(test_create, 0.25);
        else if (!strcmp(argv[i], "2")) sd_run_test(test_isEmpty, 0.25);
        else if (!strcmp(argv[i], "3")) sd_run_test(test_insert, 2);
        else if (!strcmp(argv[i], "4")) sd_run_test(test_length, 0.5);
        else if (!strcmp(argv[i], "5")) sd_run_test(test_contains, 0.5);
        else if (!strcmp(argv[i], "6")) sd_run_test(test_deleteOnce, 2);
        else if (!strcmp(argv[i], "7")) sd_run_test(test_getNth, 0.5);
    }
    return 0;
}

/*
    Main function to run all or selected tests.
*/
int main(int argc, char **argv) {
    srand(time(NULL));
    char *result;

    if (argc == 1) {
        result = all_tests();
    } else {
        result = selective_tests(argc, argv);
    }

    if (result) {
        printf("\n❌ %s\n", result);
    } else {
        printf("\n✅ All tests passed! Total Score: %.2lf\n", total_score);
    }

    printf("Total tests run: %d\n", tests_run);
    return result != 0;
}
