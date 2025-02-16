#include <stdio.h>

typedef int T;

#include "include/SortedList.h"

/*
  Generates a sorted linked list with numbers from A to B.
*/
TSortedList getNaturals(int A, int B) {
    TSortedList nats = NULL;
    // Insert in reverse to maintain sorted order
    for (int i = B; i >= A; i--)
        nats = insert(nats, i);
    return nats;
}

/*
  Generates a sorted list of prime numbers up to N using the Sieve of Eratosthenes.
*/
TSortedList getPrimes(int N) {
    if (N < 2) return NULL;

    TSortedList primes = getNaturals(2, N);
    TSortedList lp1 = primes, lp2, prev;

    while (lp1 != NULL && lp1->value * lp1->value <= N) {
        lp2 = lp1->next;
        prev = lp1;

        while (lp2 != NULL) {
            if (lp2->value % lp1->value == 0) {
                prev->next = lp2->next;
                TSortedList temp = lp2;
                lp2 = lp2->next;
                free(temp);
            } else {
                prev = lp2;
                lp2 = lp2->next;
            }
        }

        lp1 = lp1->next;
    }

    return primes;
}

/*
  Prints the elements of a sorted linked list.
*/
void printInts(TSortedList list) {
    while (!isEmpty(list)) {
        printf("%d ", list->value);
        list = list->next;
    }
    printf("\n");
}

/*
  Frees the memory allocated for the sorted list.
*/
void freeList(TSortedList list) {
    while (list != NULL) {
        TSortedList temp = list;
        list = list->next;
        free(temp);
    }
}

int main() {
    TSortedList primes = getPrimes(100);
    printInts(primes);
    freeList(primes);
    return 0;
}
