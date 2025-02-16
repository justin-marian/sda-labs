#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <stdio.h>
#include <stdlib.h>

#include "list.h"

#define INFINITY 999999

/* ========================== STRUCTURES ========================== */

/**
 * Structure representing a **Graph**.
 * - `V`: Number of vertices.
 * - `type`: Graph type (`0` = undirected, `1` = directed).
 * - `adjLists`: Adjacency list representation.
 * - `visited`: Array to track visited nodes.
 * - `start`, `end`: Arrays for time discovery (used in DFS).
 */
typedef struct graph {
	int V;
	int type;
	List *adjLists;
	int *visited;
	int *start;
	int *end;
} *Graph;

/**
 * Structure representing an **Edge** in the graph.
 */
typedef struct edge {
	int u, v, cost;
} Edge;

/* ========================== FUNCTION DECLARATIONS ========================== */

/**
 * Initializes a **graph** with `V` vertices.
 * - If the graph is **undirected**, `type = 0`.
 * - If the graph is **directed**, `type = 1`.
 * 
 * @param V Number of vertices.
 * @param type Graph type (0 = undirected, 1 = directed).
 * @return A pointer to the initialized graph.
 */
Graph initGraph(int V, int type);

/**
 * Adds an **edge** between `u` and `v` with weight `cost`.
 * - If the graph is **not weighted**, set `cost = 0`.
 * - If the graph is **undirected**, also adds edge (`v`, `u`).
 * 
 * @param graph Pointer to the graph.
 * @param u Start vertex.
 * @param v End vertex.
 * @param cost Weight of the edge.
 * @return The updated graph.
 */
Graph insertEdge(Graph graph, int u, int v, int cost);

/**
 * Prints the adjacency list representation of the graph.
 * 
 * @param graph Pointer to the graph.
 */
void printGraph(Graph graph);

/**
 * Draws the graph (placeholder function for visualization).
 * 
 * @param graph Pointer to the graph.
 * @param name Name of the graph.
 */
void drawGraph(Graph graph, const char *name);

/**
 * Checks if there is an **edge** between `u` and `v`.
 * 
 * @param graph Pointer to the graph.
 * @param u Start vertex.
 * @param v End vertex.
 * @return `1` if edge exists, `0` otherwise.
 */
int isArc(Graph graph, int u, int v);

/**
 * Retrieves the **cost** of the edge (`u`, `v`).
 * - Returns `INFINITY` if `u` and `v` are **not connected**.
 * 
 * @param graph Pointer to the graph.
 * @param u Start vertex.
 * @param v End vertex.
 * @return The cost of the edge (`u`, `v`) or `INFINITY` if not connected.
 */
int getCost(Graph graph, int u, int v);

/**
 * Frees all **memory** allocated for the graph.
 * 
 * @param graph Pointer to the graph.
 */
void freeGraph(Graph graph);

/* ========================================================================== */

#endif /* __GRAPH_H__ */
