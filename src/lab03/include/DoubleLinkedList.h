#ifndef _DOUBLE_LINKED_LIST_H_
#define _DOUBLE_LINKED_LIST_H_

#include <stdlib.h>

/*
  IMPORTANT!

  Since we use pure C, we cannot use templates.
  We assume that type `Item` is previously defined.
*/

// -----------------------------------------------------------------------------
// Data Structures
// -----------------------------------------------------------------------------

/**
 *  Node structure for the double linked list.
 */
typedef struct ListNode {
    Item elem;
    struct ListNode* next;
    struct ListNode* prev;
} ListNode;

/**
 *  Double linked list structure.
 */
typedef struct List {
    ListNode* first;
    ListNode* last;
} List;

// -----------------------------------------------------------------------------
// List Operations
// -----------------------------------------------------------------------------

/**
 * Creates a new node with the given element.
 * 
 * @param elem The value to store in the node.
 * @return A pointer to the newly created node.
 */
ListNode* createNode(Item elem) {
    ListNode* node = (ListNode*)malloc(sizeof(ListNode));
    if (!node) return NULL;

    node->elem = elem;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

/**
 * Creates a new empty list.
 * 
 * @return A pointer to the newly created empty list.
 */
List* createList(void) {
    List* list = (List*)malloc(sizeof(List));
    if (!list) return NULL;

    list->first = NULL;
    list->last = NULL;
    return list;
}

/**
 * Determines if the list is empty.
 * 
 * @param list A pointer to the list.
 * @return 1 if the list is empty, 0 otherwise.
 */
int isEmpty(List* list) {
    return (list == NULL || (list->first == NULL && list->last == NULL));
}

/**
 * Checks if the list contains a given element.
 * 
 * @param list A pointer to the list.
 * @param elem The element to search for.
 * @return 1 if the element is found, 0 otherwise.
 */
int contains(List* list, Item elem) {
    if (list == NULL) return 0;

    ListNode* p = list->first;
    while (p != NULL) {
        if (p->elem == elem)
            return 1;
        p = p->next;
    }
    return 0;
}

/**
 * Inserts an element at a specified position in the list.
 * 
 * @param list A pointer to the list.
 * @param elem The element to insert.
 * @param pos The position (0-based index) at which to insert the element.
 */
void insertAt(List* list, Item elem, int pos) {
    if (list == NULL) return;

    ListNode* current = list->first;
    while (pos && current != NULL) {
        pos--;
        current = current->next;
    }

    if (pos == 0) {
        ListNode* node = createNode(elem);
        if (!node) return;

        // If the list is empty
        if (isEmpty(list)) {
            list->first = list->last = node;
            return;
        }

        // If inserting at the end
        if (current == NULL) {
            node->prev = list->last;
            list->last->next = node;
            list->last = node;
            return;
        }

        // If inserting at the beginning
        if (current->prev == NULL) {
            node->next = current;
            current->prev = node;
            list->first = node;
            return;
        }

        // General case (inserting in the middle)
        node->prev = current->prev;
        node->next = current;
        current->prev->next = node;
        current->prev = node;
    }
}

/**
 * Deletes the first occurrence of an element from the list.
 * 
 * @param list A pointer to the list.
 * @param elem The element to delete.
 */
void deleteOnce(List* list, Item elem) {
    if (list == NULL || list->first == NULL || !contains(list, elem)) 
        return;

    ListNode* node = list->first;

    // If the element is in the first node
    if (node->elem == elem) {
        if (node->next == NULL) {  
			// Only one element in the list
            list->first = list->last = NULL;
        } else {
            list->first = node->next;
            list->first->prev = NULL;
        }
        free(node);
        return;
    }

    // Traverse the list to find the element
    while (node != NULL && node->elem != elem) {
        node = node->next;
    }

    if (node == NULL) return;

    // If the element is found in the middle
    if (node->next != NULL) {
        node->next->prev = node->prev;
        node->prev->next = node->next;
    } 

    // If the element is the last node
    if (node == list->last) {
        list->last = list->last->prev;
        list->last->next = NULL;
    }

    free(node);
}

/**
 * Computes the length of the list.
 * 
 * @param list A pointer to the list.
 * @return The number of elements in the list.
 */
int length(List* list) {
    if (list == NULL) return 0;

    int len = 0;
    ListNode* node = list->first;
    while (node != NULL) {
        len++;
        node = node->next;
    }
    return len;
}

/**
 * Destroys the list and frees its memory.
 * 
 * @param list A pointer to the list.
 * @return A NULL pointer after destruction.
 */
List* destroyList(List* list) {
    if (list == NULL) return NULL;

    ListNode* current = list->first;
    while (current != NULL) {
        ListNode* temp = current;
        current = current->next;
        free(temp);
    }

    free(list);
    return NULL;
}

#endif //_DOUBLE_LINKED_LIST_H_
