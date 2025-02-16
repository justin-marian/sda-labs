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

/**
 * Utility functions for character lists.
 */

/**
 * Prints the list from head to tail.
 */
void printList(List *list) {
    if (isEmpty(list)) {
        printf("[]");
        return;
    }

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
    if (isEmpty(list)) {
        printf("[]");
        return;
    }

    ListNode* iterator = list->last;
    printf("[");
    while (iterator != list->first) {
        printf("%c, ", iterator->elem);
        iterator = iterator->prev;
    }
    printf("%c]", list->first->elem);
}

/**
 * Checks if the given list represents a palindrome.
 * 
 * @param list A pointer to the doubly linked list.
 * @return 1 if the list is a palindrome, 0 otherwise.
 */
int isPalindrome(List* list) {
    if (list == NULL || isEmpty(list)) {
        return 0;
    }

    ListNode* left = list->first;
    ListNode* right = list->last;

    while (left != right && left->prev != right) {
        if (left->elem != right->elem) {
            return 0;
        }
        left = left->next;
        right = right->prev;
    }

    return 1;
}

int main(void) {
    int len, inputCount = 0;
    char inputCharacters[MAX_INPUT_LEN + 1];

    FILE* inputFile = fopen("../data/input", "r");
    if (inputFile == NULL) {
        fprintf(stderr, "Error: Could not open file 'input'.\n");
        return 1;
    }

    while (fgets(inputCharacters, MAX_INPUT_LEN, inputFile) != NULL) {
        // Remove trailing CR/LF (i.e. '\r', '\n')
        inputCharacters[strcspn(inputCharacters, "\r\n")] = 0;
        len = strlen(inputCharacters);

        if (len == 0) break; 

        // Create the list and insert characters
        List *list = createList();
        if (!list) {
            fprintf(stderr, "Error: Memory allocation failed for list.\n");
            fclose(inputFile);
            return 1;
        }

        for (int i = 0; i < len; i++) {
            insertAt(list, inputCharacters[i], i);
        }

        // Display the input and list
        printf("Input%d: ", ++inputCount);
        printf("\"%s\" --- List: ", inputCharacters);
        printList(list);

        // Check and print if it's a palindrome
        if (isPalindrome(list)) {
            printf(" is a palindrome.");
        } else {
            printf(" is NOT a palindrome.");
        }
        printf("\n");

        // Free memory and destroy the list
        list = destroyList(list);
    }

    fclose(inputFile);
    return 0;
}
