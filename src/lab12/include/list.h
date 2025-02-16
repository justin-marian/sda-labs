#ifndef __LIST_H__
#define __LIST_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* ========================== STRUCTURES ========================== */

/**
 * Structure representing a pair of values: 
 * - `v`    : vertex (or identifier).
 * - `cost` : associated weight or cost.
 */
typedef struct pair {
	int v, cost;
} Pair;

typedef Pair V;

/**
 * Structure representing a **doubly linked list node**.
 * - `data` : Stores the pair (vertex, cost).
 * - `prev` : Pointer to the previous node.
 * - `next` : Pointer to the next node.
 */
typedef struct list {
	V data;
	struct list *prev, *next;
} *List;

/* ========================== FUNCTION DECLARATIONS ========================== */

/**
 * Initializes a **new list** with a single node containing `data`.
 * @param data The value to store in the new node.
 * @return Pointer to the newly created list (first node).
 */
List initList(V data);

/**
 * Adds a **new node at the beginning** of the list.
 * @param list Pointer to the existing list.
 * @param data Value to be inserted.
 * @return Updated list pointer with the new first element.
 */
List addFirst(List list, V data);

/**
 * Adds a **new node at the end** of the list.
 * @param list Pointer to the existing list.
 * @param data Value to be inserted.
 * @return Updated list pointer.
 */
List addLast(List list, V data);

/**
 * Deletes the **first occurrence** of `data` from the list.
 * @param list Pointer to the existing list.
 * @param data Value to be removed.
 * @return Updated list pointer after deletion.
 */
List deleteItem(List list, V data);

/**
 * Frees all **memory allocated** for the list.
 * @param list Pointer to the existing list.
 * @return NULL after freeing all elements.
 */
List freeList(List list);

/* ========================================================================== */

#endif /* __LIST_H__ */
