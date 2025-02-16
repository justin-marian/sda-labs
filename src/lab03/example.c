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
 * Utility function prototypes for character lists.
 */
void printList(List *list);
void printListReverse(List* list);

int main(void) {
    int len;
    char inputCharacters[MAX_INPUT_LEN + 1];
    List *list = createList();

    printf("Enter a string of characters: ");
    
    // Read user input
    fgets(inputCharacters, MAX_INPUT_LEN, stdin);

    // Remove trailing CR/LF (i.e. '\r', '\n')
    inputCharacters[strcspn(inputCharacters, "\r\n")] = 0;

    // Insert the read characters into the list
    len = strlen(inputCharacters);
    for (int i = 0; i < len; i++) {
        insertAt(list, inputCharacters[i], i);
    }

    // Display the generated list
    printf("Generated list: ");
    printList(list);
    printf("\n\n");

    // Removing the first character
    deleteOnce(list, inputCharacters[0]);
    printf("List after deleting the first character: ");
    printList(list);
    printf("\n");

    // Removing the last character
    insertAt(list, inputCharacters[0], 0);
    deleteOnce(list, inputCharacters[len - 1]);
    printf("List after deleting the last character: ");
    printList(list);
    printf("\n");

    // Removing the middle character
    insertAt(list, inputCharacters[len - 1], len - 1);
    deleteOnce(list, inputCharacters[(len - 1) / 2]);
    printf("List after deleting the middle character: ");
    printList(list);
    printf("\n");

    // Destroy the list
    list = destroyList(list);
    return 0;
}

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
