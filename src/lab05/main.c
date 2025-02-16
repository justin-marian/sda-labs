#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "include/tree.h"

// -------------------------- TESTING MACROS --------------------------

#define sd_assert(message, test) \
    do { \
        if (!(test)) { \
            printf("❌ Test failed: %s\n", message); \
            return message; \
        } \
    } while (0)

#define sd_run_test(test, score) \
    do { \
        char *message = test(); \
        tests_run++; \
        if (message) { \
            return message; \
        } else { \
            total_score += score; \
            printf("✅ Passed! Score: %.2lf\n", 1.0 * score); \
        } \
    } while (0)

// Global variables for tracking test results
int tests_run = 0;
float total_score = 0;

// -------------------------- TESTING MACROS --------------------------

// Test data
int test1[] = {9, 7, 5, 9, 4, 10, 6, 8, -8, 12};
int test2[] = {11, 9, 7, 25, 12, 29, 27, 8, 5, 1, 35, 26};
int test3[] = {26, 50, 150, 35, 175, 155, 100, 95, 9, 15, 45, 40, 4, 47, 98, 
	97, 99, 90, 200, 50, 68, 35, 39, 37, 44, 43, 46};

// -------------------------- UTILITIES --------------------------

/**
 * @brief Checks if the given tree is a valid BST.
 */
 int checkBST(Tree node) { 
	if (node == NULL) return 1;
	if (node->left && node->left->value > node->value) return 0;
	if (node->right && node->right->value < node->value) return 0;
	return checkBST(node->left) && checkBST(node->right);
}

/**
 * @brief Helper function to generate DOT graph representation of the BST.
 */
void bst_print_dot_aux(Tree node, FILE* stream) {
    if (!node) return;
    if (node->left) {
        fprintf(stream, "    %d -> %d;\n", node->value, node->left->value);
        bst_print_dot_aux(node->left, stream);
    }
    if (node->right) {
        fprintf(stream, "    %d -> %d;\n", node->value, node->right->value);
        bst_print_dot_aux(node->right, stream);
    }
}

/**
 * @brief Generates a DOT file to visualize the BST.
 */
void bst_print_dot(Tree tree, FILE* stream, int type) {
    fprintf(stream, "digraph BST {\n");
    fprintf(stream, "    node [fontname=\"Arial\", shape=circle, style=filled, fillcolor=%s];\n", 
        type == 1 ? "green" : "red");
    
    if (tree) bst_print_dot_aux(tree, stream);
    fprintf(stream, "}\n");
}

// -------------------------- TEST CASES --------------------------

static char *test_insert() {
	Tree tree = NULL;
	FILE *f;
	int i;

	for (i = 1; i <= test1[0]; i++) {
		tree = insert(tree, test1[i]);
	}
	f = fopen("test.dot", "w");
	bst_print_dot(tree, f, 1);
	fclose(f);
	system("dot test.dot | neato -n -Tpng -o out_tree1.png");
	sd_assert("Cerința 1 - Test1 insert picat", checkBST(tree) && tree != NULL);
	freeTree(&tree);

	tree = NULL;
	for (i = 1; i <= test2[0]; i++) {
		tree = insert(tree, test2[i]);
	}
	f = fopen("test.dot", "w");
	bst_print_dot(tree, f, 1);
	fclose(f);
	system("dot test.dot | neato -n -Tpng -o out_tree2.png");
	sd_assert("Cerința 1 - Test2 insert picat", checkBST(tree) && tree != NULL);
	freeTree(&tree);
	
	tree = NULL;
	for (i = 1; i <= test3[0]; i++) {
		tree = insert(tree, test3[i]);
	}
	f = fopen("test.dot", "w");
	bst_print_dot(tree, f, 1);
	fclose(f);
	system("dot test.dot | neato -n -Tpng -o out_tree3.png");
	sd_assert("Cerința 1 - Test3 insert picat", checkBST(tree) && tree != NULL);
	freeTree(&tree);
	printf("insert - Toate testele au trecut!\n");
	return 0;
}

static char *test_preorder() {
	printf("\npreorder - Testele sunt verificate manual!\n");
	Tree tree = NULL;
	int i;

	for (i = 1; i <= test1[0]; i++) {
		tree = insert(tree, test1[i]);
	}
	printf("\tpreorder - Testul 1: [7 5 4 -8 6 9 8 10 12]\n");
	printPreorder(tree);
	printf("\n\n");
	freeTree(&tree);

	tree = NULL;
	for (i = 1; i <= test2[0]; i++) {
		tree = insert(tree, test2[i]);
	}
	printf("\tpreorder - Testul 2: [9 7 5 1 8 25 12 29 27 26 35]\n");
	printPreorder(tree);
	printf("\n\n");
	freeTree(&tree);
	
	tree = NULL;
	for (i = 1; i <= test3[0]; i++) {
		tree = insert(tree, test3[i]);
	}
	printf("\tpreorder - Testul 3: [50 35 9 4 15 45 40 39 37 44 43 47 46 150 100 95 90 68 98 97 99 175 155 200]\n");
	printPreorder(tree);
	printf("\n\n");
	freeTree(&tree);
	return 0;
}

static char *test_postorder() {
	printf("\npostorder - Testele sunt verificate manual!\n");
	Tree tree = NULL;
	int i;

	for (i = 1; i <= test1[0]; i++) {
		tree = insert(tree, test1[i]);
	}
	printf("\tpostorder - Testul 1: [-8 4 6 5 8 12 10 9 7]\n");
	printPostorder(tree);
	printf("\n\n");
	freeTree(&tree);

	tree = NULL;
	for (i = 1; i <= test2[0]; i++) {
		tree = insert(tree, test2[i]);
	}
	printf("\tpostorder - Testul 2: [1 5 8 7 12 26 27 35 29 25 9]\n");
	printPostorder(tree);
	printf("\n\n");
	freeTree(&tree);
	
	tree = NULL;
	for (i = 1; i <= test3[0]; i++) {
		tree = insert(tree, test3[i]);
	}
	printf("\tpostorder - Testul 3: [4 15 9 37 39 43 44 40 46 47 45 35 68 90 97 99 98 95 100 155 200 175 150 50]\n");
	printPostorder(tree);
	printf("\n\n");
	freeTree(&tree);
	return 0;
}

static char *test_inorder() {
	printf("\ninorder - Testele sunt verificate manual!\n");
	Tree tree = NULL;
	int i;

	for (i = 1; i <= test1[0]; i++) {
		tree = insert(tree, test1[i]);
	}
	printf("\tinorder - Testul 1: [-8 4 5 6 7 8 9 10 12]\n");
	printInorder(tree);
	printf("\n\n");
	freeTree(&tree);

	tree = NULL;
	for (i = 1; i <= test2[0]; i++) {
		tree = insert(tree, test2[i]);
	}
	printf("\tinorder - Testul 2: [1 5 7 8 9 12 25 26 27 29 35]\n");
	printInorder(tree);
	printf("\n\n");
	freeTree(&tree);
	
	tree = NULL;
	for (i = 1; i <= test3[0]; i++) {
		tree = insert(tree, test3[i]);
	}
	printf("\tinorder - Testul 3: [4 9 15 35 37 39 40 43 44 45 46 47 50 68 90 95 97 98 99 100 150 155 175 200]\n");
	printInorder(tree);
	printf("\n\n");
	freeTree(&tree);
	return 0;
}

static char *test_maxDepth() {
	Tree tree = NULL;
	int i;

	for (i = 1; i <= test1[0]; i++) {
		tree = insert(tree, test1[i]);
	}
	sd_assert("Cerința 1 - Test1 maxDepth picat", maxDepth(tree) == 3);
	freeTree(&tree);

	tree = NULL;
	for (i = 1; i <= test2[0]; i++) {
		tree = insert(tree, test2[i]);
	}
	sd_assert("Cerința 1 - Test2 maxDepth picat", maxDepth(tree) == 4);
	freeTree(&tree);

	tree = NULL;
	for (i = 1; i <= test3[0]; i++) {
		tree = insert(tree, test3[i]);
	}
	sd_assert("Cerința 1 - Test3 maxDepth picat", maxDepth(tree) == 5);
	freeTree(&tree);
	printf("maxDepth - Toate testele au trecut!\n");
	return 0;
}

static char *test_size() {
	Tree tree = NULL;
	int i;

	for (i = 1; i <= test1[0]; i++) {
		tree = insert(tree, test1[i]);
	}
	sd_assert("Cerința 1 - Test1 size picat", size(tree) == test1[0]);
	freeTree(&tree);

	tree = NULL;
	for (i = 1; i <= test2[0]; i++) {
		tree = insert(tree, test2[i]);
	}
	sd_assert("Cerința 1 - Test2 size picat", size(tree) == test2[0]);
	freeTree(&tree);

	tree = NULL;
	for (i = 1; i <= test3[0]; i++) {
		tree = insert(tree, test3[i]);
	}
	sd_assert("Cerința 1 - Test3 size picat", size(tree) == test3[0] - 2);
	freeTree(&tree);
	printf("size - Toate testele au trecut!\n");

	return 0;
}

static char *test_free() {
	Tree tree = NULL;
	int i;

	for (i = 1; i <= test1[0]; i++) {
		tree = insert(tree, test1[i]);
	}
	freeTree(&tree);
	sd_assert("Cerința 1 - Test1 free picat", tree == NULL);
	

	tree = NULL;
	for (i = 1; i <= test2[0]; i++) {
		tree = insert(tree, test2[i]);
	}
	freeTree(&tree);
	sd_assert("Cerința 1 - Test2 free picat", tree == NULL);
	
	tree = NULL;
	for (i = 1; i <= test3[0]; i++) {
		tree = insert(tree, test3[i]);
	}
	freeTree(&tree);
	sd_assert("Cerința 1 - Test3 free picat", tree == NULL);
	printf("free - Testele sunt verificate manual!\n");

	return 0;
}

static char *test_mirror() {
	Tree tree = NULL, result = NULL;
	int i;
	FILE *f;

	for (i = 1; i <= test1[0]; i++) {
		tree = insert(tree, test1[i]);
		result = insert(result, test1[i]);
	}
	mirror(tree);
	f = fopen("test.dot", "w");
	bst_print_dot(tree, f, 3);
	fclose(f);
	system("dot test.dot | neato -n -Tpng -o out_mirror1.png");
	sd_assert("Cerința 2 - Test1 mirror picat", tree != NULL && isMirrorTree(tree, result));
	freeTree(&tree);
	freeTree(&result);

	tree = NULL;
	result = NULL;
	for (i = 1; i <= test2[0]; i++) {
		tree = insert(tree, test2[i]);
		result = insert(result, test2[i]);
	}
	mirror(tree);
	f = fopen("test.dot", "w");
	bst_print_dot(tree, f, 3);
	fclose(f);
	system("dot test.dot | neato -n -Tpng -o out_mirror2.png");
	sd_assert("Cerința 2 - Test2 mirror picat", tree != NULL && isMirrorTree(tree, result));
	freeTree(&tree);
	freeTree(&result);

	tree = NULL;
	result = NULL;
	for (i = 1; i <= test3[0]; i++) {
		tree = insert(tree, test3[i]);
		result = insert(result, test3[i]);
	}
	mirror(tree);
	f = fopen("test.dot", "w");
	bst_print_dot(tree, f, 3);
	fclose(f);
	system("dot test.dot | neato -n -Tpng -o out_mirror3.png");
	sd_assert("Cerința 2 - Test3 mirror picat", tree != NULL && isMirrorTree(tree, result));
	freeTree(&tree);
	freeTree(&result);
	printf("mirror - Toate testele au trecut!\n");

	return 0;
}

static char *test_sameTree() {
	Tree tree = NULL, result = NULL;
	int i;

	for (i = 1; i <= test1[0]; i++) {
		tree = insert(tree, test1[i]);
		result = insert(result, test1[i]);
	}
	sd_assert("Cerința 3 - Test1 isSameTree picat", isSameTree(tree, result));
	freeTree(&tree);
	freeTree(&result);

	tree = NULL;
	result = NULL;
	for (i = 1; i <= test2[0]; i++) {
		tree = insert(tree, test2[i]);
		result = insert(result, test2[i]);
	}
	sd_assert("Cerința 3 - Test2 isSameTree picat", isSameTree(tree, result));
	freeTree(&tree);
	freeTree(&result);

	tree = NULL;
	result = NULL;
	for (i = 1; i <= test3[0]; i++) {
		tree = insert(tree, test3[i]);
		result = insert(result, test3[i]);
	}
	sd_assert("Cerința 3 - Test3 isSameTree picat", isSameTree(tree, result));
	freeTree(&tree);
	freeTree(&result);
	printf("isSameTree - Toate testele au trecut!\n");

	return 0;
}

static char *run_all_tests() {
    struct {
        char *name;
        char *(*test_function)();
        float score;
    } tests[] = {
        {"Insert", test_insert, 1.5},
        {"Postorder Traversal", test_postorder, 0.75},
        {"Preorder Traversal", test_preorder, 0.75},
        {"Inorder Traversal", test_inorder, 0.75},
        {"Tree Free", test_free, 0.75},
        {"Tree Size", test_size, 0.75},
        {"Max Depth", test_maxDepth, 0.75},
        {"Mirror Tree", test_mirror, 2.0},
        {"Same Tree", test_sameTree, 2.0}
    };

    int num_tests = sizeof(tests) / sizeof(tests[0]);
    
    for (int i = 0; i < num_tests; i++) {
        printf("Running test: %s...\n", tests[i].name);
        sd_run_test(tests[i].test_function, tests[i].score);
    }
    
    return 0;
}

static char *run_selected_tests(int argc, char **argv) {
    struct {
        char *code;
        char *name;
        char *(*test_function)();
        float score;
    } tests[] = {
        {"1", "Insert", test_insert, 1.5},
        {"2", "Postorder Traversal", test_postorder, 0.75},
        {"3", "Preorder Traversal", test_preorder, 0.75},
        {"4", "Inorder Traversal", test_inorder, 0.75},
        {"5", "Tree Free", test_free, 0.75},
        {"6", "Tree Size", test_size, 0.75},
        {"7", "Max Depth", test_maxDepth, 0.75},
        {"8", "Mirror Tree", test_mirror, 2.0},
        {"9", "Same Tree", test_sameTree, 2.0}
    };

    int num_tests = sizeof(tests) / sizeof(tests[0]);
    int selected[10] = {0};

    for (int i = 1; i < argc; i++) {
        for (int j = 0; j < num_tests; j++) {
            if (!strcmp(argv[i], tests[j].code) && !selected[j]) {
                selected[j] = 1;
                printf("Running selected test: %s...\n", tests[j].name);
                sd_run_test(tests[j].test_function, tests[j].score);
            }
        }
    }

    return 0;
}

int main(int argc, char **argv) {
    srand(time(NULL));

    char *result;
    if (argc == 1) {
        printf("\nRunning all tests...\n");
        result = run_all_tests();
    } else {
        printf("\nRunning selected tests...\n");
        result = run_selected_tests(argc, argv);
    }

    if (result) {
        printf("\n❌ Some tests failed: %s\n\n", result);
    } else {
        printf("\n🎉 All tests passed successfully!\n\n");
    }

    printf("Total Score: %.2lf\n", total_score);
    printf("Total Tests Run: %d\n", tests_run);

    return result != 0;
}
