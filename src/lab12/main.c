#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "include/graph.h"
#include "include/stack.h"

/**
 * Function that checks if two integer arrays are equal.
 * @param v1 - First array
 * @param v2 - Second array
 * @param size - Size of both arrays
 * @return - 1 if arrays are equal, 0 otherwise
 */
int check(int *v1, int *v2, int size) {
    for (int i = 0; i < size; i++) {
        if (v1[i] != v2[i]) {
            return 0;
		}
    }
    return 1;
}

/**
 * Recursive DFS function used for topological sorting.
 * @param graph - The input graph
 * @param start - Starting node
 * @param stack - Stack used for storing sorted nodes
 * @return - Updated stack
 */
Stack dfs(Graph graph, int start, Stack stack) {
    List list = graph->adjLists[start];
    graph->visited[start] = 1;

    while (list) {
        if (!graph->visited[list->data.v])
            stack = dfs(graph, list->data.v, stack);
        list = list->next;
    }

    stack = push(stack, start);
    return stack;
}

/**
 * Function that performs topological sorting for a Directed Acyclic Graph (DAG).
 * @param graph - The input graph
 * @param result - Pre-allocated array where the sorted order will be stored
 */
void topologicalSort(Graph graph, int *result) {
    Stack stack = NULL;

    // Perform DFS on all unvisited nodes
    for (int i = 0; i < graph->V; i++) {
        if (!graph->visited[i]) {
            stack = dfs(graph, i, stack);
        }
    }

    // Pop elements from stack to get topological order
    int i = 0;
    while (!isEmptyStack(stack)) {
        result[i++] = top(stack);
        stack = pop(stack);
    }
}

/**
 * Function that computes the shortest paths from a single source using Bellman-Ford algorithm.
 * @param graph - The input graph
 * @param start - The starting node
 * @param distances - Pre-allocated array where the shortest distances will be stored
 */
void BellmanFord(Graph graph, int start, int *distances) {
    int V = graph->V;
    
    // Initialize distances to all nodes
    for (int i = 0; i < V; i++) {
        distances[i] = getCost(graph, start, i);
    }
    distances[start] = 0;

    // Relax edges (V - 1) times
    for (int i = 0; i < V - 2; i++) {
        for (int j = 0; j < V; j++) {
            List list = graph->adjLists[j];
            while (list) {
                int u = j;
                int v = list->data.v;
                if (distances[u] != INFINITY && distances[v] > distances[u] + list->data.cost) {
                    distances[v] = distances[u] + list->data.cost;
                }
                list = list->next;
            }
        }
    }
}

/**
 * Function that computes the shortest paths between all pairs using Floyd-Warshall algorithm.
 * @param graph - The input graph
 * @param distances - Pre-allocated 2D array where the shortest distances will be stored
 */
void FloydWarshall(Graph graph, int **distances) {
    int V = graph->V;

    // Initialize distance matrix
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            distances[i][j] = getCost(graph, i, j);
        }
    }

    // Floyd-Warshall Algorithm
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                int cost = getCost(graph, i, k);
                if (cost == INFINITY || distances[k][j] == INFINITY) continue;
                if (distances[i][j] > distances[k][j] + cost) {
                    distances[i][j] = distances[k][j] + cost;
                }
            }
        }
    }
}

void executeTopologicalSort(Graph graph, int *expected, double *score) {
    int *result = calloc(graph->V, sizeof(int));
    if (!result) {
        fprintf(stderr, "Error: Memory allocation failed for topological sort result.\n");
        return;
    }

    topologicalSort(graph, result);

    printf("\nTopological Sort Result: ");
    for (int i = 0; i < graph->V; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    if (check(result, expected, graph->V)) {
        printf("Correct\n");
        *score += 1.5;
    } else {
        printf("Incorrect\n");
    }

    free(result);
}

void executeBellmanFord(Graph graph, int *expected, double *score) {
    int *distances = calloc(graph->V, sizeof(int));
    if (!distances) {
        fprintf(stderr, "Error: Memory allocation failed for Bellman-Ford distances.\n");
        return;
    }

    BellmanFord(graph, 0, distances);

    printf("\nBellman-Ford Result: ");
    for (int i = 0; i < graph->V; i++) {
        printf("%d ", distances[i]);
    }
    printf("\n");

    if (check(distances, expected, graph->V)) {
        printf("Correct\n");
        *score += 1.5;
    } else {
        printf("Incorrect\n");
    }

    free(distances);
}

void executeFloydWarshall(Graph graph, char *referenceFile, double *score) {
    int **distances = malloc(graph->V * sizeof(int *));
    if (!distances) {
        fprintf(stderr, "Error: Memory allocation failed for Floyd-Warshall distance matrix.\n");
        return;
    }

    for (int i = 0; i < graph->V; i++) {
        distances[i] = calloc(graph->V, sizeof(int));
        if (!distances[i]) {
            fprintf(stderr, "Error: Memory allocation failed for Floyd-Warshall row.\n");
            return;
        }
    }

    FloydWarshall(graph, distances);

    printf("\nFloyd-Warshall Result:\n");
    FILE *fin = fopen(referenceFile, "r");
    if (!fin) {
        fprintf(stderr, "Error: Unable to open reference file: %s\n", referenceFile);
        return;
    }

    int correct = 1, cost;
    for (int i = 0; i < graph->V; i++) {
        for (int j = 0; j < graph->V; j++) {
            printf("%6d ", distances[i][j]);
            fscanf(fin, "%d", &cost);
            if (cost != distances[i][j]) {
                correct = 0;
            }
        }
        free(distances[i]);
        printf("\n");
    }

    fclose(fin);
    free(distances);

    if (correct) {
        printf("Correct\n");
        *score += 1.5;
    } else {
        printf("Incorrect\n");
    }
}

void processGraph(
	char *inputFile, char *outputGraphFile, 
	int *expectedTopoSort, int *expectedBellmanFord, char *fwRefFile, 
	double *score) 
{
    freopen(inputFile, "r", stdin);

    int V, type, M, x, y, cost;
    scanf("%d %d", &V, &type);

    Graph graph = initGraph(V, type);
    if (!graph) {
        fprintf(stderr, "Error: Failed to initialize graph.\n");
        return;
    }

    scanf("%d", &M);
    for (int i = 0; i < M; i++) {
        scanf("%d %d %d", &x, &y, &cost);
        graph = insertEdge(graph, x, y, cost);
    }

    printGraph(graph);
    drawGraph(graph, outputGraphFile);

    // Execute algorithms
    executeTopologicalSort(graph, expectedTopoSort, score);
    executeBellmanFord(graph, expectedBellmanFord, score);
    executeFloydWarshall(graph, fwRefFile, score);

    // Free graph memory
	freeGraph(graph);
}

int main() {
    double totalScore = 0.0;

    // Test case 1
    int top1[] = {0, 3, 2, 1, 4, 5};
    int res1[] = {0, 1, 3, 5, 0, 3};

    printf("=============================================\n");
    printf("Processing test case: test0.in\n");
    processGraph("../data/test0.in", "graph0.dot", top1, res1, "../data/test0.ref", &totalScore);

    // Test case 2
    int top2[][7] = {
        {0, 3, 5, 2, 1, 4, 6}, {0, 3, 2, 1, 4, 5, 6},
        {0, 3, 2, 1, 5, 4, 6}, {0, 3, 2, 5, 1, 4, 6}
    };
    int res2[] = {0, 1, 3, 5, 0, 4, 3};

    printf("=============================================\n");
    printf("Processing test case: test1.in\n");
    processGraph("../data/test1.in", "graph1.dot", top2[0], res2, "../data/test1.ref", &totalScore);

    printf("=============================================\n");
    printf("Total Score: %.2lf\n", totalScore);
    printf("Note: 1 bonus point is awarded if no memory leaks/errors occur.\n");

    return 0;
}