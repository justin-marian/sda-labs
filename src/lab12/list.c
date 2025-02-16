#include "include/list.h"

/**
 * Initializes a **new list** with a single node containing `data`.
 */
List initList(V data)
{
    List list = (List) malloc(sizeof(struct list));
    if (!list) {
        fprintf(stderr, "Error: Memory allocation failed for list node.\n");
        return NULL;
    }

    list->data = data;
    list->next = NULL;
    list->prev = NULL;
    return list;
}

/**
 * Adds a **new node at the beginning** of the list.
 */
List addFirst(List list, V data)
{
    List newNode = initList(data);
    if (!newNode) return list;

    newNode->next = list;
    if (list) list->prev = newNode;
    return newNode;
}

/**
 * Adds a **new node at the end** of the list.
 */
List addLast(List list, V data)
{
    if (!list) return initList(data);

    List newNode = initList(data);
    if (!newNode) return list;

    List temp = list;
    while (temp->next) temp = temp->next;

    temp->next = newNode;
    newNode->prev = temp;
    return list;
}

/**
 * Deletes the **first occurrence** of `data` from the list.
 */
List deleteItem(List list, V data) {
    if (!list) return NULL;

    List temp = list;

    // If the head node needs to be deleted
    if (temp->data.v == data.v && temp->data.cost == data.cost) {
        list = temp->next;
        if (list) list->prev = NULL;
        free(temp);
        return list;
    }

    while (temp && (temp->data.v != data.v || temp->data.cost != data.cost))
        temp = temp->next;

    if (!temp) return list;

    if (temp->prev) temp->prev->next = temp->next;
    if (temp->next) temp->next->prev = temp->prev;

    free(temp);
    return list;
}

/**
 * Frees all **memory allocated** for the list.
 */
List freeList(List list)
{
    while (list) {
        List temp = list;
        list = list->next;
        free(temp);
    }
    return NULL;
}
