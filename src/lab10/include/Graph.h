#ifndef GRAPH_H_
#define GRAPH_H_

#include "Util.h"

/**
 * @brief Node structure for the adjacency list representation of a graph.
 *
 * Each node represents a destination vertex in the adjacency list.
 */
typedef struct TNode {
  int v;
  struct TNode *next;
} TNode, *ATNode;

/**
 * @brief Graph representation using an adjacency list.
 *
 * This structure stores the number of vertices and an array of adjacency lists.
 */
typedef struct {
  int nn;
  ATNode *adl;
} TGraphL;

/**
 * @brief Creates a graph with a specified number of vertices.
 *
 * Allocates memory for the adjacency list and initializes it.
 *
 * @param numberOfNodes The number of vertices in the graph.
 * @return Pointer to the created graph, or NULL if memory allocation fails.
 */
TGraphL *createGraphAdjList(int numberOfNodes);

/**
 * @brief Adds an undirected edge between two vertices.
 *
 * This function adds an edge (v1 ↔ v2) by updating both adjacency lists.
 *
 * @param graph Pointer to the graph.
 * @param v1 First vertex.
 * @param v2 Second vertex.
 */
void addEdgeList(TGraphL *graph, int v1, int v2);

/**
 * @brief Removes an undirected edge between two vertices.
 *
 * This function removes the edge (v1 ↔ v2) from both adjacency lists.
 *
 * @param graph Pointer to the graph.
 * @param v1 First vertex.
 * @param v2 Second vertex.
 */
void removeEdgeList(TGraphL *graph, int v1, int v2);

/**
 * @brief Removes a node and all its associated edges from the graph.
 *
 * This function removes all edges associated with a given vertex.
 *
 * @param graph Pointer to the graph.
 * @param v Vertex to remove.
 */
void removeNodeList(TGraphL *graph, int v);

/**
 * @brief Performs a Depth-First Search (DFS) traversal of the graph.
 *
 * Starts from a given vertex and explores as far as possible along each branch.
 *
 * @param graph Pointer to the graph.
 * @param s Starting vertex.
 * @return Pointer to a list containing the DFS traversal order.
 */
List *dfs(TGraphL *graph, int s);

/**
 * @brief Performs a Breadth-First Search (BFS) traversal of the graph.
 *
 * Explores all neighbors of a vertex before moving to the next level.
 *
 * @param graph Pointer to the graph.
 * @param s Starting vertex.
 * @return Pointer to a list containing the BFS traversal order.
 */
List *bfs(TGraphL *graph, int s);

/**
 * @brief Frees all allocated memory for the graph.
 *
 * This function properly deallocates the adjacency list and all associated
 * nodes.
 *
 * @param graph Pointer to the graph.
 */
void destroyGraphAdjList(TGraphL *graph);

#endif /* GRAPH_H_ */
