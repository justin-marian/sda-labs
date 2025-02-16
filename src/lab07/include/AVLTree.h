#ifndef AVLTREE_H
#define AVLTREE_H

#include <stdlib.h>

// -----------------------------------------------------------------------------
// AVL Tree Node Structure
// -----------------------------------------------------------------------------
typedef struct AVLNode {
    long* elem;
    int height;
    struct AVLNode *l;
    struct AVLNode *r;
    struct AVLNode *p;
} AVLNode;

// AVL Tree Structure
typedef struct AVLTree {
    long size;
    AVLNode* root;
    AVLNode* nil;
    int (*comp)(long* a, long* b);
} AVLTree;

// -----------------------------------------------------------------------------
// AVL TREE FUNCTIONS
// -----------------------------------------------------------------------------

// Create a new AVL Tree
AVLTree* avlCreateTree(int (*comp)(long* a, long* b)) {
    AVLTree* newTree = (AVLTree*)malloc(sizeof(AVLTree));
    if (!newTree) return NULL;

    newTree->comp = comp;

    // Create NIL node
    newTree->nil = (AVLNode*)malloc(sizeof(AVLNode));
    if (!newTree->nil) {
        free(newTree);
        return NULL;
    }

	// Sentinel node does not hold data
    newTree->nil->p = newTree->nil->l = newTree->nil->r = newTree->nil;
    newTree->nil->height = 0;
    newTree->nil->elem = NULL;

    // Create root node
    newTree->root = newTree->nil;
    newTree->size = 0;

    return newTree;
}

// Check if the tree is empty
int avlIsEmpty(AVLTree* tree) {
    if (!tree) return 1;
    return (tree->root == tree->nil);
}

// Create a new node
AVLNode* avlNewNode(AVLTree* tree, long* elem) {
    AVLNode* newNode = (AVLNode*)malloc(sizeof(AVLNode));
    if (!newNode) return NULL;
    
    newNode->elem = elem;
    newNode->p = newNode->r = newNode->l = tree->nil;
    newNode->height = 1;
    return newNode;
}

// -----------------------------------------------------------------------------
// AVL TREE ROTATIONS
// -----------------------------------------------------------------------------

// Get maximum of two numbers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Left rotation
void avlLeftRotate(AVLTree *tree, AVLNode *x) {
    if (x == tree->nil || x->r == tree->nil) return;

    AVLNode *y = x->r;
    y->p = x->p;
    x->r = y->l;

    if (y->l != tree->nil)
        y->l->p = x;

    if (x->p == tree->nil)
        tree->root = y;
    else if (x == x->p->l)
        x->p->l = y;
    else
        x->p->r = y;

    y->l = x;
    x->p = y;

    x->height = max(x->l->height, x->r->height) + 1;
    y->height = max(y->l->height, y->r->height) + 1;
}

// Right rotation
void avlRightRotate(AVLTree *tree, AVLNode *y) {
    if (y == tree->nil || y->l == tree->nil) return;

    AVLNode *x = y->l;
    x->p = y->p;
    y->l = x->r;

    if (x->r != tree->nil)
        x->r->p = y;

    if (y->p == tree->nil)
        tree->root = x;
    else if (y == y->p->l)
        y->p->l = x;
    else
        y->p->r = x;

    x->r = y;
    y->p = x;

    y->height = max(y->l->height, y->r->height) + 1;
    x->height = max(x->l->height, x->r->height) + 1;
}

// Get balance factor
int avlGetBalance(AVLNode *x) {
    if (!x || x->elem == NULL) return 0;
    return (x->l != NULL ? x->l->height : 0) - (x->r != NULL ? x->r->height : 0);
}

// -----------------------------------------------------------------------------
// AVL TREE INSERTION
// -----------------------------------------------------------------------------

void avlInsert(AVLTree *tree, long* elem) {
    if (!tree || !elem) return;

    AVLNode *x = tree->root, *y = tree->nil;
    AVLNode *newNode = avlNewNode(tree, elem);
    if (!newNode) return;

    while (x != tree->nil) {
        y = x;
        if (tree->comp(elem, x->elem) < 0)
            x = x->l;
        else
            x = x->r;
    }

    newNode->p = y;
    if (y == tree->nil)
        tree->root = newNode;
    else if (tree->comp(elem, y->elem) < 0)
        y->l = newNode;
    else
        y->r = newNode;

    tree->size++;

    // Balance the tree
    while (y != tree->nil) {
        y->height = max(y->l->height, y->r->height) + 1;
        int balance = avlGetBalance(y);

        if (balance > 1 && tree->comp(elem, y->l->elem) < 0)
            avlRightRotate(tree, y);
        else if (balance < -1 && tree->comp(elem, y->r->elem) > 0)
            avlLeftRotate(tree, y);
        else if (balance > 1 && tree->comp(elem, y->l->elem) > 0) {
            avlLeftRotate(tree, y->l);
            avlRightRotate(tree, y);
        } else if (balance < -1 && tree->comp(elem, y->r->elem) < 0) {
            avlRightRotate(tree, y->r);
            avlLeftRotate(tree, y);
        }

        y = y->p;
    }
}

// -----------------------------------------------------------------------------
// AVL TREE DESTRUCTION
// -----------------------------------------------------------------------------

void avlDestroyTreeHelper(AVLTree* tree, AVLNode* node) {
    if (node == tree->nil) return;
    avlDestroyTreeHelper(tree, node->l);
    avlDestroyTreeHelper(tree, node->r);
    free(node->elem);
    free(node);
}

// Delete the AVL Tree
void avlDestroyTree(AVLTree* tree) {
    if (!tree) return;
    avlDestroyTreeHelper(tree, tree->root);
    free(tree->nil);
    free(tree);
}

#endif /* AVLTREE_H */
