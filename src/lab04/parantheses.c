#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LEN 256

typedef char Item;

#include "include/Stack.h"

int isBalanced(const char *str, int length) {
    Stack* stack = createStack();
    if (!stack) {
        fprintf(stderr, "Error: Failed to allocate stack.\n");
        return 0;
    }

    for (int i = 0; i < length; i++) {
        char current = str[i];

        // If it's an opening bracket, push it to stack
        if (current == '(' || current == '[' || current == '{') {
            push(stack, current);
        } else if (current == ')' || current == ']' || current == '}') {
            if (isStackEmpty(stack)) {
                destroyStack(stack);
                return 0;  // Unmatched closing bracket
            }

            char top = stack->head->elem;
            pop(stack);

            // Check if the popped bracket matches the closing bracket
            if ((current == ')' && top != '(') ||
                (current == ']' && top != '[') ||
                (current == '}' && top != '{')) {
                destroyStack(stack);
                return 0;  // Mismatched brackets
            }
        }
    }

    int balanced = isStackEmpty(stack);
    destroyStack(stack);
    return balanced;
}

int main() {
    char buffer[MAX_INPUT_LEN];
    
    FILE* inputFile = fopen("../data/input-parantheses.txt", "r");
    if (!inputFile) {
        fprintf(stderr, "Error: Could not open input-parantheses.txt\n");
        return EXIT_FAILURE;
    }

    while (fgets(buffer, MAX_INPUT_LEN, inputFile) != NULL) {
        buffer[strcspn(buffer, "\r\n")] = 0;
        int len = strlen(buffer);
        if (len == 0) continue;

        if (isBalanced(buffer, len))
            printf("%s ---> is balanced.\n", buffer);
        else
            printf("%s ---> not balanced.\n", buffer);
    }

    fclose(inputFile);
    return EXIT_SUCCESS;
}
