#include <stdio.h>
#include <stdlib.h>

#include "include/tree.h"

/*
   Function that creates a tree with a single node
*/
Tree createTree(Item value) {
    Tree root = malloc(sizeof(TreeNode));
    if (!root) {
        fprintf(stderr, "Error: Memory allocation failed for root.\n");
        exit(EXIT_FAILURE);
    }
    root->value = value;
    root->left = NULL;
    root->right = NULL;
    return root;
}

/*
   Function that initializes a tree node
*/
void init(Tree *root, Item value) {
    if (!root) return;

    *root = malloc(sizeof(TreeNode));
    if (!*root) {
        fprintf(stderr, "Error: Memory allocation failed for node.\n");
        exit(EXIT_FAILURE);
    }
    (*root)->value = value;
    (*root)->left = NULL;
    (*root)->right = NULL;
}

/*
   Function that inserts a value into a binary search tree
*/
Tree insert(Tree root, Item value) {
    if (root == NULL) {
        init(&root, value);
        return root;
    }

    if (root->value == value)
        return root;  // The node already exists

    if (root->value > value) {
        root->left = insert(root->left, value);
    } else {
        root->right = insert(root->right, value);
    }
    return root;
}

/*
   Function that prints the tree using postorder traversal
*/
void printPostorder(Tree root) {
    if (!root) return;
    printPostorder(root->left);
    printPostorder(root->right);
    printf("%d ", root->value);
}

/*
   Function that prints the tree using preorder traversal
*/
void printPreorder(Tree root) {
    if (!root) return;
    printf("%d ", root->value);
    printPreorder(root->left);
    printPreorder(root->right);
}

/*
   Function that prints the tree using inorder traversal
*/
void printInorder(Tree root) {
    if (!root) return;
    printInorder(root->left);
    printf("%d ", root->value);
    printInorder(root->right);
}

/*
   Function that deallocates the entire binary tree
*/
void freeTree(Tree *root) {
    if (!root || !(*root)) return;

    freeTree(&((*root)->left));
    freeTree(&((*root)->right));

    free(*root);
    *root = NULL; // Ensure root pointer is set to NULL after deallocation
}

/*
   Function that determines the number of nodes in a binary tree
*/
int size(Tree root) {
    if (!root) return 0;
    return 1 + size(root->left) + size(root->right);
}

/*
   Function that returns the maximum depth of the tree
*/
int maxDepth(Tree root) {
    if (!root) return -1;  // Change to `0` if needed for test compatibility
    int leftDepth = maxDepth(root->left);
    int rightDepth = maxDepth(root->right);
    return (leftDepth > rightDepth ? leftDepth : rightDepth) + 1;
}

/*
   Function that constructs the mirror image of a binary tree
*/
void mirror(Tree root) {
    if (!root) return;

    mirror(root->left);
    mirror(root->right);

    // Swap left and right subtrees
    Tree temp = root->left;
    root->left = root->right;
    root->right = temp;
}

/*
   Function that checks if two binary trees are identical
*/
int isSameTree(Tree root1, Tree root2) {
    if (!root1 && !root2) return 1;
    if (!root1 || !root2) return 0;
    if (root1->value != root2->value) return 0;

    return isSameTree(root1->left, root2->left) && isSameTree(root1->right, root2->right);
}

/*
   Function that checks if two binary trees are mirror images of each other
*/
int isMirrorTree(Tree root1, Tree root2) {
    if (!root1 && !root2) return 1;
    if (!root1 || !root2) return 0;
    if (root1->value != root2->value) return 0;

    return isMirrorTree(root1->left, root2->right) && isMirrorTree(root1->right, root2->left);
}
