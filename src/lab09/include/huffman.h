#ifndef __HUFFMAN_H__
#define __HUFFMAN_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ASCII 256
#define MAX  1000

typedef struct HuffmanNode {
    unsigned char value;
    struct HuffmanNode *left;
    struct HuffmanNode *right;
    struct HuffmanNode *parent;
} HuffmanNode, *PHuffmanNode;

#define T PHuffmanNode

#include "heap.h"

PHuffmanNode initNode(unsigned char value);
PHuffmanNode makeTree(int freqs[ASCII]);
void freeTree(PHuffmanNode root);

void compute_freqs(const char *text, int freqs[ASCII]);
void huffman_codes(PHuffmanNode root, char *arr, char **allCodes);
void make_codes(PHuffmanNode root, char **allCodes);

char *compress(const char *textToEncode, char **allCodes);
char *decompress(const char *textToDecode, PHuffmanNode root);

// ---------------- Huffman Tree Functions ----------------

PHuffmanNode initNode(unsigned char value) {
    PHuffmanNode node = (PHuffmanNode)malloc(sizeof(HuffmanNode));
    if (!node) {
        fprintf(stderr, "Error: Memory allocation failed for Huffman node.\n");
        exit(EXIT_FAILURE);
    }

    node->left = node->right = node->parent = NULL;
    node->value = value;
    return node;
}

void compute_freqs(const char *text, int freqs[ASCII]) {
    memset(freqs, 0, ASCII * sizeof(int));
    for (int i = 0; text[i] != '\0'; ++i) {
        freqs[(unsigned char)text[i]]++;
    }
}

PHuffmanNode makeTree(int freqs[ASCII]) {
    PHeap heap = makeHeap(ASCII);
    if (!heap) {
        fprintf(stderr, "Error: Heap allocation failed!\n");
        return NULL;
    }

    for (int i = 0; i < ASCII; i++) {
        if (freqs[i] > 0) {
            PHuffmanNode node = initNode(i);
            if (!node) {
                fprintf(stderr, "Error: Huffman node allocation failed!\n");
                freeHeap(heap);
                return NULL;
            }
            insert(heap, node, freqs[i]);
        }
    }

    while (heap->size > 1) {
        PHeapNode aux1 = removeMin(heap);
        PHeapNode aux2 = removeMin(heap);
        if (!aux1 || !aux2) {
            fprintf(stderr, "Error: Heap node removal failed!\n");
            freeHeap(heap);
            return NULL;
        }

        PHuffmanNode newnode = initNode('$');
        if (!newnode) {
            fprintf(stderr, "Error: Internal node allocation failed!\n");
            freeHeap(heap);
            return NULL;
        }

        PHuffmanNode leftNode = (PHuffmanNode)aux1->elem;
        PHuffmanNode rightNode = (PHuffmanNode)aux2->elem;

        newnode->left = leftNode;
        newnode->right = rightNode;
        leftNode->parent = rightNode->parent = newnode;

        insert(heap, newnode, aux1->prior + aux2->prior);

        free(aux1);
        free(aux2);
    }

    PHuffmanNode root = (PHuffmanNode)heap->nodes[0]->elem;
    freeHeap(heap);
    return root;
}

// ---------------- Huffman Code Generation ----------------

void huffman_codes(PHuffmanNode root, char *arr, char **allCodes) {
    if (!root) return;

    if (!root->left && !root->right) {
        int index = (int)root->value;

        allCodes[index] = (char *)malloc((strlen(arr) + 1) * sizeof(char));
        if (!allCodes[index]) {
            fprintf(stderr, "Error: Memory allocation failed for character %c\n", root->value);
            exit(EXIT_FAILURE);
        }

        strcpy(allCodes[index], arr);
        return;
    }

    char *leftArr = (char *)malloc(strlen(arr) + 2);
    char *rightArr = (char *)malloc(strlen(arr) + 2);

    if (!leftArr || !rightArr) {
        fprintf(stderr, "Error: Memory allocation failed for Huffman traversal.\n");
        exit(EXIT_FAILURE);
    }

    strcpy(leftArr, arr);
    strcpy(rightArr, arr);
    strcat(leftArr, "0");
    strcat(rightArr, "1");

    huffman_codes(root->left, leftArr, allCodes);
    huffman_codes(root->right, rightArr, allCodes);

    free(leftArr);
    free(rightArr);
}

void make_codes(PHuffmanNode root, char **allCodes) {
    char arr[ASCII];

    if (!root || !allCodes) return;

    memset(arr, 0, ASCII * sizeof(char));
    memset(allCodes, 0, ASCII * sizeof(char *));

    huffman_codes(root, arr, allCodes);
}

// ---------------- Compression & Decompression ----------------

char *compress(const char *textToEncode, char **allCodes) {
    if (!textToEncode || !allCodes) return NULL;

    size_t total_size = 1; // \0

    for (int i = 0; textToEncode[i] != '\0'; i++) {
        int c = (int)textToEncode[i];
        if (allCodes[c]) {
            total_size += strlen(allCodes[c]);
        }
    }

    char *compressed = (char *)malloc(total_size * sizeof(char));
    if (!compressed) {
        fprintf(stderr, "Error: Memory allocation failed for compression.\n");
        exit(EXIT_FAILURE);
    }
    compressed[0] = '\0';

    printf("\n[DEBUG] Compression Process:\n");
    for (int i = 0; textToEncode[i] != '\0'; i++) {
        int c = (int)textToEncode[i];
        if (allCodes[c]) {
            printf("Encoding '%c' -> %s\n", c, allCodes[c]);
            strcat(compressed, allCodes[c]);
        }
    }

    printf("[DEBUG] Final Encoded String: %s\n", compressed);
    return compressed;
}

char *decompress(const char *textToDecode, PHuffmanNode root) {
    if (!textToDecode || !root) return NULL;

    char *decompressed = (char *)calloc(MAX, sizeof(char));
    if (!decompressed) {
        fprintf(stderr, "Error: Memory allocation failed for decompression.\n");
        exit(EXIT_FAILURE);
    }

    printf("\n[DEBUG] Decompression Process:\n");
    int i = 0;
    PHuffmanNode pass = root;
    char c[2] = {0, 0};

    while (textToDecode[i] != '\0') {
        if (!pass->left && !pass->right) {
            c[0] = pass->value;
            strcat(decompressed, c);
            printf("Decoded to '%c'\n", c[0]);
            pass = root;
            continue;
        }
        pass = (textToDecode[i] == '0') ? pass->left : pass->right;
        i++;
    }

    c[0] = pass->value;
    strcat(decompressed, c);
    printf("[DEBUG] Final Decoded String: %s\n", decompressed);
    return decompressed;
}

void freeTree(PHuffmanNode root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

#endif /* __HUFFMAN_H__ */
