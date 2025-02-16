#ifndef UTIL_H_
#define UTIL_H_

/**
 * @brief Node structure for a doubly linked list.
 *
 * Each node contains a key value and pointers to the previous and next nodes.
 */
typedef struct ListNode {
  int key;
  struct ListNode *next;
  struct ListNode *prev;
} ListNode;

/**
 * @brief Doubly linked list structure.
 *
 * This list supports basic operations and serves as a foundation for
 * stack and queue implementations.
 */
typedef struct List {
  ListNode *head;
} List;

typedef List Stack;
typedef List Queue;

/**
 * @brief Creates an empty doubly linked list.
 *
 * @return Pointer to the newly allocated list, or NULL if memory allocation
 * fails.
 */
List *createList(void);

/**
 * @brief Destroys a list and frees all associated memory.
 *
 * @param list Pointer to the list to be destroyed.
 */
void destroyList(List *list);

/**
 * @brief Checks if a list is empty.
 *
 * @param list Pointer to the list.
 * @return 1 if the list is empty, 0 otherwise.
 */
int isListEmpty(List *list);

/**
 * @brief Creates an empty stack.
 *
 * @return Pointer to the newly allocated stack, or NULL if memory allocation
 * fails.
 */
Stack *createStack(void);

/**
 * @brief Destroys a stack and frees all associated memory.
 *
 * @param stack Pointer to the stack to be destroyed.
 */
void destroyStack(Stack *stack);

/**
 * @brief Pushes an element onto the stack.
 *
 * @param stack Pointer to the stack.
 * @param key Value to be pushed onto the stack.
 */
void push(Stack *stack, int key);

/**
 * @brief Pops an element from the stack.
 *
 * @param stack Pointer to the stack.
 */
void pop(Stack *stack);

/**
 * @brief Checks if the stack is empty.
 *
 * @param stack Pointer to the stack.
 * @return 1 if the stack is empty, 0 otherwise.
 */
int isStackEmpty(Stack *stack);

/**
 * @brief Returns the top element of the stack.
 *
 * @param stack Pointer to the stack.
 * @return The top element, or -1 if the stack is empty.
 */
int top(Stack *stack);

/**
 * @brief Creates an empty queue.
 *
 * @return Pointer to the newly allocated queue, or NULL if memory allocation
 * fails.
 */
Queue *createQueue(void);

/**
 * @brief Destroys a queue and frees all associated memory.
 *
 * @param queue Pointer to the queue to be destroyed.
 */
void destroyQueue(Queue *queue);

/**
 * @brief Adds an element to the end of the queue.
 *
 * @param queue Pointer to the queue.
 * @param key Value to be enqueued.
 */
void enqueue(Queue *queue, int key);

/**
 * @brief Removes an element from the front of the queue.
 *
 * @param queue Pointer to the queue.
 */
void dequeue(Queue *queue);

/**
 * @brief Checks if the queue is empty.
 *
 * @param queue Pointer to the queue.
 * @return 1 if the queue is empty, 0 otherwise.
 */
int isQueueEmpty(Queue *queue);

/**
 * @brief Returns the front element of the queue.
 *
 * @param queue Pointer to the queue.
 * @return The front element, or -1 if the queue is empty.
 */
int front(Queue *queue);

#endif /* UTIL_H_ */
