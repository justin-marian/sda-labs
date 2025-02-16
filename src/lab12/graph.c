#include <string.h>

#include "include/graph.h"

/**
 * Function that initializes a graph with a specific number of nodes.
 * @param V - number of nodes in the graph
 * @param type - 0 for an undirected graph, 1 for a directed graph
 * @return - a pointer to the Graph structure
 */
Graph initGraph(int V, int type) {
    if (V <= 0) {
        fprintf(stderr, "Error: Invalid number of vertices.\n");
        return NULL;
    }

    // Allocate memory for the graph structure
    Graph graph = (Graph) malloc(sizeof(struct graph));
    if (!graph) {
        fprintf(stderr, "Error: Memory allocation failed for graph.\n");
        return NULL;
    }

    graph->V = V;
    graph->type = type;

    // Initialize adjacency lists and auxiliary vectors
    graph->adjLists = (List*) calloc(V, sizeof(List));
    graph->visited = (int*) calloc(V, sizeof(int));
    graph->start = (int*) malloc(V * sizeof(int));
    graph->end = (int*) malloc(V * sizeof(int));

    // Verify correct memory allocation
    if (!graph->adjLists || !graph->visited || !graph->start || !graph->end) {
        fprintf(stderr, "Error: Memory allocation failed for graph components.\n");
        freeGraph(graph);
        return NULL;
    }

    return graph;
}

/**
 * Function that adds an edge between nodes u and v.
 * @param graph - pointer to the graph
 * @param u - first node
 * @param v - second node
 * @param cost - cost of the edge
 * @return - the modified graph
 */
Graph insertEdge(Graph graph, int u, int v, int cost) {
    if (!graph || u < 0 || v < 0 || u >= graph->V || v >= graph->V) {
        fprintf(stderr, "Error: Invalid edge (%d, %d).\n", u, v);
        return graph;
    }

    // Add edge u -> v
    Pair p = {v, cost};
    graph->adjLists[u] = addLast(graph->adjLists[u], p);

    // If the graph is undirected, also add edge v -> u
    if (graph->type == 0) {
        Pair p1 = {u, cost};
        graph->adjLists[v] = addLast(graph->adjLists[v], p1);
    }

    return graph;
}

/**
 * Function that checks if there is an edge between two nodes.
 * @param graph - pointer to the graph
 * @param u - first node
 * @param v - second node
 * @return - 1 if the edge exists, 0 otherwise
 */
int isArc(Graph graph, int u, int v) {
    if (!graph || u < 0 || v < 0 || u >= graph->V || v >= graph->V) return 0;

    List tmp = graph->adjLists[u];
    while (tmp) {
        if (tmp->data.v == v) return 1;
        tmp = tmp->next;
    }
    return 0;
}

/**
 * Function that returns the cost of the edge between two nodes.
 * @param graph - pointer to the graph
 * @param u - first node
 * @param v - second node
 * @return - cost of the edge or INFINITY if the edge does not exist
 */
int getCost(Graph graph, int u, int v) {
    if (!graph || u < 0 || v < 0 || u >= graph->V || v >= graph->V) return INFINITY;

    List tmp = graph->adjLists[u];
    while (tmp) {
        if (tmp->data.v == v) return tmp->data.cost;
        tmp = tmp->next;
    }
    return INFINITY;
}

/**
 * Function that draws the graph and generates an image using Graphviz.
 * @param graph - pointer to the graph
 * @param name - output file name
 */
 void drawGraph(Graph g, const char *name) {
    if (!g || !name) return;

    FILE *stream = fopen(name, "w");
    if (!stream) {
        fprintf(stderr, "Error: Could not open file for writing: %s\n", name);
        return;
    }

    // Choose format based on graph type (directed or undirected)
    fprintf(stream, "%s G {\n", g->type == 0 ? "graph" : "digraph");
    fprintf(stream, "    node [fontname=\"Arial\", shape=circle, style=filled, fillcolor=yellow];\n");

    // Generate the edge list
    for (int i = 0; i < g->V; i++) {
        List tmp = g->adjLists[i];
        while (tmp) {
            if (g->type == 0 && i < tmp->data.v)
                fprintf(stream, "    %d -- %d;\n", i, tmp->data.v);
            else if (g->type == 1)
                fprintf(stream, "    %d -> %d;\n", i, tmp->data.v);
            tmp = tmp->next;
        }
    }
    fprintf(stream, "}\n");
    fclose(stream);

    // Allocate memory for `aux` dynamically
    size_t name_len = strlen(name);
    char *aux = (char *)malloc(name_len + 1);  // Allocate based on name size
    if (!aux) {
        fprintf(stderr, "Error: Memory allocation failed for aux.\n");
        return;
    }
    strncpy(aux, name, name_len);  
    aux[name_len] = '\0';

    // Remove `.dot` extension if present
    size_t len = strlen(aux);
    if (len > 4 && strcmp(aux + len - 4, ".dot") == 0) {
        aux[len - 4] = '\0';  // Remove ".dot" extension
    }

    size_t buffer_size = name_len + 12;  // extra space 
    char *buffer = (char *)malloc(buffer_size);
    if (!buffer) {
        fprintf(stderr, "Error: Memory allocation failed for buffer.\n");
        free(aux);
        return;
    }

    snprintf(buffer, buffer_size, "dot %s | neato -n -Tpng -o %s.png", name, aux);
    if (system(buffer) == -1) {
        fprintf(stderr, "Error: Failed to execute Graphviz command.\n");
    }

    free(aux);
    free(buffer);
}

/**
 * Function that prints the graph structure to the console.
 * @param graph - pointer to the graph
 */
void printGraph(Graph graph) {
    if (!graph) return;

    printf("%s with %d nodes\n", (graph->type == 0) ? \
			"Undirected graph" : "Directed graph", graph->V);

    for (int i = 0; i < graph->V; i++) {
        printf("%d: ", i);
        List adj = graph->adjLists[i];
        while (adj) {
            printf("(%d, %d) -> ", adj->data.v, adj->data.cost);
            adj = adj->next;
        }
        printf("NULL\n");
    }
}

/**
 * Function that frees the allocated memory for a graph.
 * @param graph - pointer to the graph
 */
void freeGraph(Graph graph) {
    if (!graph) return;

    // Free memory for adjacency lists
    if (graph->adjLists) {
        for (int i = 0; i < graph->V; i++) {
            graph->adjLists[i] = freeList(graph->adjLists[i]);
        }
        free(graph->adjLists);
    }

    // Free memory for auxiliary vectors
    free(graph->visited);
    free(graph->start);
    free(graph->end);
    free(graph);
}
