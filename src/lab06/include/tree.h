#ifndef _TREE_H_
#define _TREE_H_

#include <stdio.h>
#include <stdlib.h>

typedef int Item;

typedef struct node {
    Item value;
    struct node *left;
    struct node *right;
    struct node *parent;
} TreeNode, *Tree;

/*
 * Function Prototypes
 */

// Tree Initialization & Basic Operations
Tree createTree(Tree parent, Item value);           // Create a tree with a single node
void init(Tree *root, Tree parent, Item value);     // Initialize a node
int isEmpty(Tree root);                             // Check if tree is empty

// Insertion & Deletion
Tree insert(Tree root, Item value);                 // Insert an item into the BST
Tree delete(Tree root, Item value);                 // Remove an item from the BST

// Search & Queries
int contains(Tree root, Item value);                // Check if the tree contains a value
Tree find(Tree root, Item value);                   // Find a node by value

// Min & Max Operations
Tree minimum(Tree root);                            // Find the minimum value in the BST
Tree maximum(Tree root);                            // Find the maximum value in the BST

// Successor & Predecessor
Tree successor(Tree root, Item value);              // Find the in-order successor
Tree predecessor(Tree root, Item value);            // Find the in-order predecessor

// Lowest Common Ancestor (LCA)
Tree lowestCommonAncestor(Tree root, Item value1, Item value2);  

// Utility Functions
void destroyTree(Tree *root);
void printTree(Tree root, int space);

#endif  // _TREE_H_
