#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long* Item;
typedef int Info;

#include "include/AVLTree.h"

// -----------------------------------------------------------------------------
// Macros for Testing
#define ASSERT(cond, msg) 	\
	if (!(cond)) 			\
	{ 						\
		testFailed(msg); 	\ 
		return 0; 			\
	}

void testPassed(char* s) {
    printf("✅ Test %s passed successfully!\n", s);
}

void testFailed(char* s) {
    printf("❌ Test %s FAILED!\n", s);
}

// -----------------------------------------------------------------------------

// Comparison function for AVLTree
int compare(Item a, Item b) {
    if (!a || !b) return -2;
    return (*a > *b) - (*a < *b);
}

// Function to allocate an element
Item allocateElement(long elem) {
    Item heapElem = (Item)malloc(sizeof(long));
    if (heapElem) *heapElem = elem;
    return heapElem;
}

// Function to check if an AVL tree is balanced
int isBalanced(AVLTree* tree, AVLNode* node) {
    if (node == tree->nil) return 1;

    int leftHeight = isBalanced(tree, node->l);
    if (leftHeight == -1) return 0;

    int rightHeight = isBalanced(tree, node->r);
    if (rightHeight == -1) return 0;

    return (abs(leftHeight - rightHeight) <= 1) 
        ? (1 + (leftHeight > rightHeight ? leftHeight : rightHeight)) : -1;
}

// -----------------------------------------------------------------------------

// Test AVLTree Initialization
int testInitialize(AVLTree** tree) {
    *tree = avlCreateTree(compare);
    ASSERT((*tree) != NULL, "Init-00");
    ASSERT((*tree)->root != NULL, "Init-01");
    ASSERT((*tree)->nil != NULL, "Init-02");
    ASSERT((*tree)->root->l == (*tree)->nil, "Init-03");
    ASSERT((*tree)->root->r == (*tree)->nil, "Init-04");
    ASSERT(avlIsEmpty(*tree) == 1, "IsEmpty-01");

    testPassed("Initialize & IsEmpty");
    return 1;
}

// Test AVLTree Insertion
int testInsertion(AVLTree** tree) {
    *tree = avlCreateTree(compare);

    avlInsert(*tree, allocateElement(5));
    ASSERT(!avlIsEmpty(*tree), "Insert-01");
    ASSERT(*((*tree)->root->elem) == 5, "Insert-02");
    
    avlInsert(*tree, allocateElement(3));
    avlInsert(*tree, allocateElement(2));
    avlInsert(*tree, allocateElement(4));
    avlInsert(*tree, allocateElement(7));
    avlInsert(*tree, allocateElement(6));
    avlInsert(*tree, allocateElement(8));

    // Check AVL rotations (tree remains balanced)
    ASSERT(isBalanced(*tree, (*tree)->root) != -1, "Insert-AVL Balance Failed");
    
    testPassed("Insertion");
    return 1;
}

// Test AVLTree Memory Deallocation
int testDeallocate(AVLTree **tree) {
    avlDestroyTree(*tree);
    testPassed("Deallocate");
    return 1;
}

// -----------------------------------------------------------------------------

// Test Suite Structure
typedef struct {
    int (*testFunction)(AVLTree** tree);
} Test;

int main() {
    Test tests[] = {
        { testInitialize },
        { testInsertion },
        { testDeallocate }
    };

    int testsNo = sizeof(tests) / sizeof(Test);
    AVLTree* tree = NULL;

    for (int i = 0; i < testsNo; i++) {
        tests[i].testFunction(&tree);
    }

    return 0;
}
