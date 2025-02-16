#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/Graph.h"
#include "include/Util.h"

// ---------------------- Create Graph ----------------------
TGraphL *createGraphAdjList(int numberOfNodes) {
  if (numberOfNodes < 0)
    return NULL; // Invalid input check

  TGraphL *graph = (TGraphL *)malloc(sizeof(TGraphL));
  if (!graph) {
    fprintf(stderr, "Error: Memory allocation failed for graph structure.\n");
    return NULL;
  }

  graph->nn = numberOfNodes;
  graph->adl = NULL;

  if (numberOfNodes == 0) {
    return graph; // Empty graph, no adjacency list needed
  }

  graph->adl = (ATNode *)calloc(numberOfNodes, sizeof(ATNode));
  if (!graph->adl) {
    fprintf(stderr, "Error: Memory allocation failed for adjacency list.\n");
    free(graph); // Prevent memory leak
    return NULL;
  }

  return graph;
}

// ---------------------- Add Edge ----------------------
void addEdgeList(TGraphL *graph, int v1, int v2) {
  if (!graph || !graph->adl || v1 < 0 || v2 < 0 || v1 >= graph->nn ||
      v2 >= graph->nn)
    return;

  TNode *newNode1 = (TNode *)malloc(sizeof(TNode));
  if (!newNode1) {
    fprintf(stderr, "Error: Memory allocation failed for edge.\n");
    return;
  }
  newNode1->v = v2;
  newNode1->next = graph->adl[v1];
  graph->adl[v1] = newNode1;

  TNode *newNode2 = (TNode *)malloc(sizeof(TNode));
  if (!newNode2) {
    fprintf(stderr, "Error: Memory allocation failed for edge.\n");
    free(newNode1); // Prevent memory leak
    return;
  }
  newNode2->v = v1;
  newNode2->next = graph->adl[v2];
  graph->adl[v2] = newNode2;
}

// ---------------------- DFS Traversal ----------------------
void dfsRecHelper(const TGraphL *graph, int *visited, List *path, int s) {
  if (!graph || !visited || !path || s < 0 || s >= graph->nn)
    return;

  visited[s] = 1;
  push(path, s);

  for (TNode *nod = graph->adl[s]; nod; nod = nod->next) {
    if (!visited[nod->v]) {
      dfsRecHelper(graph, visited, path, nod->v);
    }
  }
}

List *dfs(TGraphL *graph, int s) {
  if (!graph || s < 0 || s >= graph->nn)
    return createList();

  int *visited = (int *)calloc(graph->nn, sizeof(int));
  if (!visited) {
    fprintf(stderr, "Error: Memory allocation failed for visited array.\n");
    return createList();
  }

  List *path = createList();
  dfsRecHelper(graph, visited, path, s);

  free(visited);
  return path;
}

// ---------------------- BFS Traversal ----------------------
List *bfs(TGraphL *graph, int s) {
  if (!graph || s < 0 || s >= graph->nn)
    return createList();

  Queue *q = createQueue();
  List *path = createList();
  int *visited = (int *)calloc(graph->nn, sizeof(int));

  if (!q || !path || !visited) {
    fprintf(stderr, "Error: Memory allocation failed for BFS.\n");
    if (q)
      destroyQueue(q);
    if (path)
      destroyList(path);
    if (visited)
      free(visited);
    return createList();
  }

  enqueue(q, s);
  visited[s] = 1;

  while (!isQueueEmpty(q)) {
    int v = front(q);
    dequeue(q);
    push(path, v);

    for (TNode *nod = graph->adl[v]; nod; nod = nod->next) {
      if (!visited[nod->v]) {
        enqueue(q, nod->v);
        visited[nod->v] = 1;
      }
    }
  }

  destroyQueue(q);
  free(visited);
  return path;
}

// ---------------------- Remove Edge ----------------------
void removeEdgeList(TGraphL *graph, int v1, int v2) {
  if (!graph || !graph->adl || v1 < 0 || v2 < 0 || v1 >= graph->nn ||
      v2 >= graph->nn)
    return;

  TNode **it = &(graph->adl[v1]);
  while (*it && (*it)->v != v2) {
    it = &((*it)->next);
  }
  if (*it) {
    TNode *temp = *it;
    *it = (*it)->next;
    free(temp);
  }

  it = &(graph->adl[v2]);
  while (*it && (*it)->v != v1) {
    it = &((*it)->next);
  }
  if (*it) {
    TNode *temp = *it;
    *it = (*it)->next;
    free(temp);
  }
}

// ---------------------- Remove Node ----------------------
void removeNodeList(TGraphL *graph, int v) {
  if (!graph || !graph->adl || v < 0 || v >= graph->nn)
    return;

  while (graph->adl[v]) {
    removeEdgeList(graph, v, graph->adl[v]->v);
  }
}

// ---------------------- Destroy Graph ----------------------
void destroyGraphAdjList(TGraphL *graph) {
  if (!graph)
    return;

  if (graph->nn > 0 && graph->adl) {
    for (int i = 0; i < graph->nn; i++) {
      TNode *temp;
      while (graph->adl[i]) {
        temp = graph->adl[i];
        graph->adl[i] = graph->adl[i]->next;
        free(temp);
      }
    }
    free(graph->adl);
  }

  free(graph);
}
