#include "include/tree.h"

/*
  Function that creates a tree with a single node.
 */
Tree createTree(Tree parent, Item value) {
    Tree root = malloc(sizeof(TreeNode));
    if (!root) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    root->parent = parent;
    root->value = value;
    root->left = NULL;
    root->right = NULL;
    return root;
}

/*
  Function that initializes a tree node.
 */
void init(Tree *root, Tree parent, Item value) {
    if (!root) return;

    *root = malloc(sizeof(TreeNode));
    if (!*root) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    (*root)->value = value;
    (*root)->parent = parent;
    (*root)->left = NULL;
    (*root)->right = NULL;
}

/*
  Function that checks if the tree is empty.
  Returns 1 if empty, otherwise 0.
 */
int isEmpty(Tree root) {
    return root == NULL;
}

/*
  Function that inserts a value into the BST.
 */
Tree insert(Tree root, Item value) {
    if (!root) {
        init(&root, NULL, value);
        return root;
    }

    if (value < root->value) {
        if (!root->left) 
            init(&(root->left), root, value);
        else 
            root->left = insert(root->left, value);
    } else if (value > root->value) {
        if (!root->right) 
            init(&(root->right), root, value);
        else 
            root->right = insert(root->right, value);
    }

    return root;
}

/*
  Function that checks if a value exists in the BST.
  Returns 1 if found, otherwise 0.
 */
int contains(Tree root, Item value) {
    if (!root) return 0;
    if (root->value == value) return 1;
    return (value < root->value) ? contains(root->left, value) : contains(root->right, value);
}

/*
  Function that finds the node containing a specific value.
 */
Tree find(Tree root, Item value) {
    if (!root || root->value == value) return root;
    return (value < root->value) ? find(root->left, value) : find(root->right, value);
}

/*
  Function that finds the minimum value in the BST.
 */
Tree minimum(Tree root) {
    if (!root) return NULL;
    while (root->left) root = root->left;
    return root;
}

/*
  Function that finds the maximum value in the BST.
 */
Tree maximum(Tree root) {
    if (!root) return NULL;
    while (root->right) root = root->right;
    return root;
}

/*
  Function that finds the in-order successor of a given value.
 */
Tree successor(Tree root, Item value) {
    Tree node = find(root, value);
    if (!node) return NULL;

    if (node->right) return minimum(node->right);

    Tree succ = node->parent;
    while (succ && node == succ->right) {
        node = succ;
        succ = succ->parent;
    }
    return succ;
}

/*
  Function that finds the in-order predecessor of a given value.
 */
Tree predecessor(Tree root, Item value) {
    Tree node = find(root, value);
    if (!node) return NULL;

    if (node->left) return maximum(node->left);

    Tree pred = node->parent;
    while (pred && node == pred->left) {
        node = pred;
        pred = pred->parent;
    }
    return pred;
}

/*
  Function that deletes a node with a given value from the BST.
 */
Tree delete(Tree root, Item value) {
    if (!root) return root;

    if (value < root->value) {
        root->left = delete(root->left, value);
    } else if (value > root->value) {
        root->right = delete(root->right, value);
    } else {
        // Node with one child or no child
        if (!root->left) {
            Tree temp = root->right;
            free(root);
            return temp;
        } else if (!root->right) {
            Tree temp = root->left;
            free(root);
            return temp;
        }

        // Node with two children: Get the in-order successor
        Tree temp = minimum(root->right);
        root->value = temp->value;
        root->right = delete(root->right, temp->value);
    }

    return root;
}

/*
  Function that finds the lowest common ancestor of two values.
 */
Tree lowestCommonAncestor(Tree root, Item value1, Item value2) {
    if (!root) return NULL;

    if (root->value > value1 && root->value > value2)
        return lowestCommonAncestor(root->left, value1, value2);

    if (root->value < value1 && root->value < value2)
        return lowestCommonAncestor(root->right, value1, value2);

    return root;
}

/*
  Function that frees the memory of the entire BST.
 */
void destroyTree(Tree *root) {
    if (!*root) return;
    destroyTree(&((*root)->left));
    destroyTree(&((*root)->right));
    free(*root);
    *root = NULL;
}
