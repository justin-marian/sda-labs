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

int test1[] = {9, 7, 5, 9, 4, 10, 6, 8, -8, 12};
int test2[] = {11, 9, 7, 25, 12, 29, 27, 8, 5, 1, 35, 26};
int test3[] = {26, 50, 150, 35, 175, 155, 100, 95, 9, 15, 45, 40, 4, 47, 98,
               97, 99, 90, 200, 50, 68, 35, 39, 37, 44, 43, 46};

/**
 * @brief Helper function to insert test values into a tree.
 */
 Tree insert_test_data(int *test_data) {
    Tree tree = NULL;
    for (int i = 1; i <= test_data[0]; i++) {
        tree = insert(tree, test_data[i]);
    }
    return tree;
}

/*
  Function that returns the height of the tree.
 */
int height(Tree root) {
    if (!root) return 0;
    int left = height(root->left);
    int right = height(root->right);
    return (left > right ? left : right) + 1;
}

/*
  Function that checks if the tree is a valid BST.
 */
int checkBST(Tree node) {
    if (!node) return 1;
    
    if ((node->left && (node->left->value > node->value || node->left->parent != node)) ||
        (node->right && (node->right->value < node->value || node->right->parent != node)))
        return 0;

    return checkBST(node->left) && checkBST(node->right);
}

/*
  Helper function for generating DOT format.
 */
void bst_print_dot_aux(Tree node, FILE *stream) {
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

/*
  Function to print the BST structure in DOT format.
 */
void bst_print_dot(Tree tree, FILE *stream, int type) {
    fprintf(stream, "digraph BST {\n");
    fprintf(stream, "    node [fontname=\"Arial\", shape=circle, style=filled, fillcolor=%s];\n",
            type == 1 ? "green" : "blue");

    if (tree) {
        bst_print_dot_aux(tree, stream);
    }
    fprintf(stream, "}\n");
}

/*
 *Helper function to print min/max nodes in different colors.
 */
void bst_print_dot_aux_highlight(Tree node, FILE *stream, int highlightValue, const char *color) {
    if (!node) return;

    bst_print_dot_aux_highlight(node->left, stream, highlightValue, color);
    if (node->value == highlightValue) {
        fprintf(stream, "    %d [fontname=\"Arial\", shape=circle, style=filled, fillcolor=%s];\n", node->value, color);
    }
    bst_print_dot_aux_highlight(node->right, stream, highlightValue, color);
}

/*
  Function to highlight min and max nodes in the BST.
 */
void bst_print_dot_minmax(Tree tree, FILE *stream, int type) {
    fprintf(stream, "digraph BST {\n");
    fprintf(stream, "    node [fontname=\"Arial\", shape=circle, style=filled, fillcolor=%s];\n",
            type == 1 ? "red" : "blue");

    if (tree) {
        bst_print_dot_aux(tree, stream);
        bst_print_dot_aux_highlight(tree, stream, minimum(tree)->value, "yellow"); // Min node
        bst_print_dot_aux_highlight(tree, stream, maximum(tree)->value, "green"); // Max node
    }
    fprintf(stream, "}\n");
}

/*
  Function to highlight specific values in the BST.
 */
void bst_print_dot_values(Tree tree, FILE *stream, int type, int min, int max) {
    fprintf(stream, "digraph BST {\n");
    fprintf(stream, "    node [fontname=\"Arial\", shape=circle, style=filled, fillcolor=%s];\n",
            type == 1 ? "red" : "blue");

    if (tree) {
        bst_print_dot_aux(tree, stream);
        fprintf(stream, "    %d [fontname=\"Arial\", shape=circle, style=filled, fillcolor=yellow];\n", min);
        if (max != -1) {
            fprintf(stream, "    %d [fontname=\"Arial\", shape=circle, style=filled, fillcolor=green];\n", max);
        }
    }
    fprintf(stream, "}\n");
}

/*
  Function to highlight the Lowest Common Ancestor (LCA) in the BST.
 */
void bst_print_dot_lca(Tree tree, FILE *stream, int type, int value1, int value2, int lca) {
    fprintf(stream, "digraph BST {\n");
    fprintf(stream, "    node [fontname=\"Arial\", shape=circle, style=filled, fillcolor=%s];\n",
            type == 1 ? "red" : "blue");

    if (tree) {
        bst_print_dot_aux(tree, stream);
        fprintf(stream, "    %d [fontname=\"Arial\", shape=circle, style=filled, fillcolor=yellow];\n", value1);
        fprintf(stream, "    %d [fontname=\"Arial\", shape=circle, style=filled, fillcolor=yellow];\n", value2);
        fprintf(stream, "    %d [fontname=\"Arial\", shape=circle, style=filled, fillcolor=green];\n", lca);
    }
    fprintf(stream, "}\n");
}


/**
 * @brief Generates a DOT file and creates a PNG visualization.
 */
 void generate_dot_visual(Tree tree, const char *filename, int type, int highlight1, int highlight2) {
    FILE *f = fopen("test.dot", "w");
    if (!f) {
        fprintf(stderr, "Error: Unable to create DOT file.\n");
        return;
    }

    if (highlight1 == -1 && highlight2 == -1) {
        bst_print_dot(tree, f, type);
    } else {
        bst_print_dot_values(tree, f, type, highlight1, highlight2);
    }
    
    fclose(f);
    char command[128];
    snprintf(command, sizeof(command), "dot test.dot | neato -n -Tpng -o %s", filename);
    system(command);
}

// -------------------------- TEST CASES --------------------------

/**
 * @brief Test insert functionality.
 */
 static char *test_insert() {
    Tree tree;

    tree = insert_test_data(test1);
    generate_dot_visual(tree, "out_insert_tree1.png", 1, -1, -1);
    sd_assert("Insert Test 1 Failed", height(tree) == 4 && checkBST(tree) && tree && tree->value == 7 &&
                                       tree->left && tree->left->parent == tree);
    destroyTree(&tree);

    tree = insert_test_data(test2);
    generate_dot_visual(tree, "out_insert_tree2.png", 1, -1, -1);
    sd_assert("Insert Test 2 Failed", height(tree) == 5 && checkBST(tree) && tree && tree->value == 9 &&
                                       tree->right && tree->right->parent == tree);
    destroyTree(&tree);

    tree = insert_test_data(test3);
    generate_dot_visual(tree, "out_insert_tree3.png", 1, -1, -1);
    sd_assert("Insert Test 3 Failed", height(tree) == 6 && checkBST(tree) && tree &&
                                       tree->right && tree->left && tree->left->parent == tree->right->parent);
    destroyTree(&tree);

    printf("✅ Insert - All tests passed!\n");
    return 0;
}

/**
 * @brief Test if tree is empty.
 */
 static char *test_isEmpty() {
    Tree tree = insert_test_data(test1);
    generate_dot_visual(tree, "out_isEmpty_tree1.png", 1, -1, -1);
    sd_assert("isEmpty Test 1 Failed", !isEmpty(tree));
    destroyTree(&tree);

    tree = insert_test_data(test2);
    generate_dot_visual(tree, "out_isEmpty_tree2.png", 1, -1, -1);
    sd_assert("isEmpty Test 2 Failed", !isEmpty(tree));
    destroyTree(&tree);

    tree = insert_test_data(test3);
    generate_dot_visual(tree, "out_isEmpty_tree3.png", 1, -1, -1);
    sd_assert("isEmpty Test 3 Failed", !isEmpty(tree));
    destroyTree(&tree);

    sd_assert("isEmpty Test 4 Failed (NULL case)", isEmpty(NULL));

    printf("✅ isEmpty - All tests passed!\n");
    return 0;
}

/**
 * @brief Test finding the minimum and maximum values in a BST.
 */
 static char *test_minmax() {
    Tree tree = insert_test_data(test1);
    Tree min = minimum(tree), max = maximum(tree);
    generate_dot_visual(tree, "out_minmax1.png", 1, min->value, max->value);
    sd_assert("MinMax Test 1 Failed", min && min->value == -8 && max && max->value == 12);
    destroyTree(&tree);

    tree = insert_test_data(test2);
    min = minimum(tree), max = maximum(tree);
    generate_dot_visual(tree, "out_minmax2.png", 1, min->value, max->value);
    sd_assert("MinMax Test 2 Failed", min && min->value == 1 && max && max->value == 35);
    destroyTree(&tree);

    tree = insert_test_data(test3);
    min = minimum(tree), max = maximum(tree);
    generate_dot_visual(tree, "out_minmax3.png", 1, min->value, max->value);
    sd_assert("MinMax Test 3 Failed", min && min->value == 4 && max && max->value == 200);
    destroyTree(&tree);

    sd_assert("MinMax Test 4 Failed (NULL case)", minimum(NULL) == NULL && maximum(NULL) == NULL);

    printf("✅ MinMax - All tests passed!\n");
    return 0;
}

/**
 * @brief Test if a tree contains specific values.
 */
 static char *test_contains() {
    Tree tree = insert_test_data(test1);
    sd_assert("Contains Test 1 Failed", contains(tree, 7) && contains(tree, 10) && contains(tree, 12) &&
                                         !contains(tree, 2) && !contains(tree, 20) && contains(tree, 6));
    destroyTree(&tree);

    tree = insert_test_data(test2);
    sd_assert("Contains Test 2 Failed", contains(tree, 25) && contains(tree, 26) && contains(tree, 1) &&
                                         contains(tree, 35) && !contains(tree, 24) && !contains(tree, 28));
    destroyTree(&tree);

    tree = insert_test_data(test3);
    sd_assert("Contains Test 3 Failed", contains(tree, 155) && contains(tree, 99) && contains(tree, 43));
    destroyTree(&tree);

    printf("✅ Contains - All tests passed!\n");
    return 0;
}

/**
 * @brief Test tree deletion.
 */
 static char *test_delete() {
    Tree tree = insert_test_data(test1);
    int value = 12;
    generate_dot_visual(tree, "out_delete1_before.png", 1, value, -1);
    tree = delete(tree, value);
    generate_dot_visual(tree, "out_delete1_after.png", 1, -1, -1);
    sd_assert("Delete Test 1 Failed", height(tree) == 4 && tree && checkBST(tree) && !contains(tree, value));
    destroyTree(&tree);

    tree = insert_test_data(test2);
    value = 29;
    generate_dot_visual(tree, "out_delete2_before.png", 1, value, -1);
    tree = delete(tree, value);
    generate_dot_visual(tree, "out_delete2_after.png", 1, -1, -1);
    sd_assert("Delete Test 2 Failed", height(tree) == 5 && tree && checkBST(tree) && !contains(tree, value));
    destroyTree(&tree);

    tree = insert_test_data(test3);
    value = 50;
    generate_dot_visual(tree, "out_delete3_before.png", 1, value, -1);
    tree = delete(tree, value);
    generate_dot_visual(tree, "out_delete3_after.png", 1, -1, -1);
    sd_assert("Delete Test 3 Failed", height(tree) == 6 && tree && checkBST(tree) && !contains(tree, value));
    destroyTree(&tree);

    printf("✅ Delete - All tests passed!\n");
    return 0;
}

/**
 * @brief Test Lowest Common Ancestor (LCA).
 */
static char *test_lca() {
    Tree tree, lca;
    int value1, value2;

    tree = insert_test_data(test1);
    value1 = 12, value2 = -8;
    lca = lowestCommonAncestor(tree, value1, value2);
    sd_assert("LCA Test 1 Failed", lca && lca->value == 7);
    generate_dot_visual(tree, "out_lca1.png", 1, value1, value2);
    destroyTree(&tree);

    tree = insert_test_data(test2);
    value1 = 12, value2 = 35;
    lca = lowestCommonAncestor(tree, value1, value2);
    sd_assert("LCA Test 2 Failed", lca && lca->value == 25);
    generate_dot_visual(tree, "out_lca2.png", 1, value1, value2);
    destroyTree(&tree);

    tree = insert_test_data(test3);
    value1 = 4, value2 = 43;
    lca = lowestCommonAncestor(tree, value1, value2);
    sd_assert("LCA Test 3 Failed", lca && lca->value == 35);
    generate_dot_visual(tree, "out_lca3.png", 1, value1, value2);
    destroyTree(&tree);

    printf("✅ LCA - All tests passed!\n");
    return 0;
}

/**
 * @brief Test Successor Function.
 */
static char *test_successor() {
    Tree tree, succ;

    tree = insert_test_data(test1);
    sd_assert("Successor Test 1 Failed", (succ = successor(tree, -8)) && succ->value == 4);
    sd_assert("Successor Test 2 Failed", (succ = successor(tree, 6)) && succ->value == 7);
    sd_assert("Successor Test 3 Failed", (succ = successor(tree, 7)) && succ->value == 8);
    sd_assert("Successor Test 4 Failed", successor(tree, 12) == NULL);
    destroyTree(&tree);

    tree = insert_test_data(test2);
    sd_assert("Successor Test 5 Failed", (succ = successor(tree, 1)) && succ->value == 5);
    sd_assert("Successor Test 6 Failed", (succ = successor(tree, 8)) && succ->value == 9);
    sd_assert("Successor Test 7 Failed", (succ = successor(tree, 12)) && succ->value == 25);
    sd_assert("Successor Test 8 Failed", (succ = successor(tree, 9)) && succ->value == 12);
    sd_assert("Successor Test 9 Failed", successor(tree, 35) == NULL);
    destroyTree(&tree);

    tree = insert_test_data(test3);
    sd_assert("Successor Test 10 Failed", (succ = successor(tree, 4)) && succ->value == 9);
    sd_assert("Successor Test 11 Failed", (succ = successor(tree, 68)) && succ->value == 90);
    sd_assert("Successor Test 12 Failed", (succ = successor(tree, 47)) && succ->value == 50);
    sd_assert("Successor Test 13 Failed", (succ = successor(tree, 35)) && succ->value == 37);
    sd_assert("Successor Test 14 Failed", successor(tree, 200) == NULL);
    sd_assert("Successor Test 15 Failed", (succ = successor(tree, 99)) && succ->value == 100);
    destroyTree(&tree);

    printf("✅ Successor - All tests passed!\n");
    return 0;
}

/**
 * @brief Test Predecessor Function.
 */
static char *test_predecessor() {
    Tree tree, pred;

    tree = insert_test_data(test1);
    sd_assert("Predecessor Test 1 Failed", (pred = predecessor(tree, 4)) && pred->value == -8);
    sd_assert("Predecessor Test 2 Failed", (pred = predecessor(tree, 7)) && pred->value == 6);
    sd_assert("Predecessor Test 3 Failed", (pred = predecessor(tree, 8)) && pred->value == 7);
    sd_assert("Predecessor Test 4 Failed", predecessor(tree, -8) == NULL);
    destroyTree(&tree);

    tree = insert_test_data(test2);
    sd_assert("Predecessor Test 5 Failed", (pred = predecessor(tree, 5)) && pred->value == 1);
    sd_assert("Predecessor Test 6 Failed", (pred = predecessor(tree, 9)) && pred->value == 8);
    sd_assert("Predecessor Test 7 Failed", (pred = predecessor(tree, 25)) && pred->value == 12);
    sd_assert("Predecessor Test 8 Failed", (pred = predecessor(tree, 12)) && pred->value == 9);
    sd_assert("Predecessor Test 9 Failed", (pred = predecessor(tree, 26)) && pred->value == 25);
    destroyTree(&tree);

    tree = insert_test_data(test3);
    sd_assert("Predecessor Test 10 Failed", (pred = predecessor(tree, 9)) && pred->value == 4);
    sd_assert("Predecessor Test 11 Failed", (pred = predecessor(tree, 90)) && pred->value == 68);
    sd_assert("Predecessor Test 12 Failed", (pred = predecessor(tree, 50)) && pred->value == 47);
    sd_assert("Predecessor Test 13 Failed", (pred = predecessor(tree, 37)) && pred->value == 35);
    sd_assert("Predecessor Test 14 Failed", predecessor(tree, 4) == NULL);
    sd_assert("Predecessor Test 15 Failed", (pred = predecessor(tree, 100)) && pred->value == 99);
    sd_assert("Predecessor Test 16 Failed", (pred = predecessor(tree, 68)) && pred->value == 50);
    destroyTree(&tree);

    printf("✅ Predecessor - All tests passed!\n");
    return 0;
}

static char *all_tests() {
	sd_run_test(test_insert, 1);
	sd_run_test(test_isEmpty, 0.25);
	sd_run_test(test_contains, 0.25);
	sd_run_test(test_minmax, 1);
	sd_run_test(test_successor, 1);
	sd_run_test(test_predecessor, 1);
	sd_run_test(test_delete, 2);
	sd_run_test(test_lca, 2);
	return 0;
}

static char *selective_tests(int argc, char **argv) {
	int i;
	int viz[9] = {0};
	for (i = 1; i < argc; i++) {
		if (viz[atoi(argv[i])]) {
			continue;
		}
		if (!strcmp(argv[i], "1")) {
			viz[1] = 1;
			sd_run_test(test_insert, 1);
		} else if (!strcmp(argv[i], "2")) {
			viz[2] = 1;
			sd_run_test(test_isEmpty, 0.25);
		} else if (!strcmp(argv[i], "3")) {
			viz[3] = 1;
			sd_run_test(test_contains, 0.25);
		} else if (!strcmp(argv[i], "4")) {
			viz[4] = 1;
			sd_run_test(test_minmax, 1);
		} else if (!strcmp(argv[i], "5")) {
			viz[5] = 1;
			sd_run_test(test_successor, 1);
		} else if (!strcmp(argv[i], "6")) {
			viz[6] = 1;
			sd_run_test(test_predecessor, 1);
		} else if (!strcmp(argv[i], "7")) {
			viz[7] = 1;
			sd_run_test(test_delete, 2);
		} else if (!strcmp(argv[i], "8")) {
			viz[8] = 1;
			sd_run_test(test_lca, 2);
		}
	}
	return 0;
}

int main(int argc, char **argv) {
	srand(time(NULL));
	char *result;
	if (argc == 1) {
		result = all_tests();
		if (result != 0) {
			printf("%s\n", result);
		} else {
			printf("Toate testele au trecut! Felicitari!\n");
		}
	} else {
		result = selective_tests(argc, argv);
		if (result != 0) {
			printf("%s\n", result);
		} else {
			printf("Toate testele selectate au trecut!\n");
		}
	}
	printf("Punctajul obtinut este: %.2lf\n", total_score);
	printf("Teste rulate: %d\n", tests_run);
	return result != 0;
}
