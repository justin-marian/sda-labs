#ifndef _TREE_H_
#define _TREE_H_

#include <stdio.h>
#include <stdlib.h>

typedef int Item;

typedef struct TreeNode {
    Item value;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode, *Tree;

/**
 * @brief Initializes a tree node with a given value.
 * 
 * @param root Pointer to the root node.
 * @param value The value to be assigned to the node.
 */
void init(Tree *root, Item value);

/**
 * @brief Inserts a new value into the binary search tree.
 * 
 * @param root Root of the tree.
 * @param value Value to insert.
 * @return Updated tree root after insertion.
 */
Tree insert(Tree root, Item value);

/**
 * @brief Prints the tree in postorder traversal.
 * 
 * @param root Root of the tree.
 */
void printPostorder(Tree root);

/**
 * @brief Prints the tree in preorder traversal.
 * 
 * @param root Root of the tree.
 */
void printPreorder(Tree root);

/**
 * @brief Prints the tree in inorder traversal.
 * 
 * @param root Root of the tree.
 */
void printInorder(Tree root);

/**
 * @brief Frees all memory used by the tree and sets root to NULL.
 * 
 * @param root Pointer to the root of the tree.
 */
void freeTree(Tree *root);

/**
 * @brief Returns the number of nodes in the tree.
 * 
 * @param root Root of the tree.
 * @return Number of nodes in the tree.
 */
int size(Tree root);

/**
 * @brief Computes the maximum depth (height) of the tree.
 * 
 * @param root Root of the tree.
 * @return Maximum depth of the tree.
 */
int maxDepth(Tree root);

/**
 * @brief Mirrors the tree by swapping left and right children recursively.
 * 
 * @param root Root of the tree.
 */
void mirror(Tree root);

/**
 * @brief Checks if two trees are structurally identical and have the same values.
 * 
 * @param root1 First tree root.
 * @param root2 Second tree root.
 * @return 1 if identical, 0 otherwise.
 */
int isSameTree(Tree root1, Tree root2);

/**
 * @brief Checks if two trees are mirror images of each other.
 *
 * @param root1 First tree root.
 * @param root2 Second tree root.
 * @return 1 if mirror images, 0 otherwise.
 */
int isMirrorTree(Tree root1, Tree root2);

#endif /* _TREE_H_ */
