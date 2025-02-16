#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "include/minheap.h"

#define INF 999999

typedef int TCost;

typedef struct node {
  int v;
  TCost c;
  struct node *next;
} TNode, *ATNode;

typedef struct {
  int nn;
  ATNode *adl;
} TGraphL;

/**
 * Allocate memory for an adjacency list representation of a graph.
 * Initializes all adjacency list heads to NULL.
 */
void alloc_list(TGraphL *G, int n) {
  G->nn = n;
  G->adl = (ATNode *)malloc(n * sizeof(ATNode));
  if (!G->adl) {
    fprintf(stderr, "Memory allocation failed for adjacency list.\n");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < n; i++)
    G->adl[i] = NULL;
}

/**
 * Inserts an undirected edge into the graph.
 */
void insert_edge_list(TGraphL *G, int v1, int v2, int c) {
  TNode *t;

  t = (TNode *)malloc(sizeof(TNode));
  t->v = v2;
  t->c = c;
  t->next = G->adl[v1];
  G->adl[v1] = t;

  t = (TNode *)malloc(sizeof(TNode));
  t->v = v1;
  t->c = c;
  t->next = G->adl[v2];
  G->adl[v2] = t;
}

/**
 * Implements Dijkstra’s algorithm using a MinHeap-based priority queue.
 */
void dijkstra(TGraphL G, int s) {
  int *dist = (int *)malloc(G.nn * sizeof(int));
  APriQueue shortpath = makeQueue(G.nn);

  for (int i = 0; i < G.nn; i++)
    dist[i] = INF;

  dist[s] = 0;
  insert(shortpath, (ItemType){s, dist[s]});

  while (shortpath->size > 0) {
    ItemType min = removeMin(shortpath);
    int u = min.content;

    for (TNode *nod = G.adl[u]; nod; nod = nod->next) {
      int v = nod->v;
      if (dist[u] + nod->c < dist[v]) {
        dist[v] = dist[u] + nod->c;
        insert(shortpath, (ItemType){v, dist[v]});
      }
    }
  }

  printf("\nVertex  Distance from Source\n");
  for (int n = 0; n < G.nn; n++)
    printf("%d\t\t%d\n", n, dist[n]);

  free(dist);
  freeQueue(shortpath);
}

/**
 * Implements Prim’s algorithm using a MinHeap-based priority queue.
 */
void Prim(TGraphL G) {
  int *P = (int *)malloc(G.nn * sizeof(int));
  int *K = (int *)malloc(G.nn * sizeof(int));
  APriQueue shortpath = makeQueue(G.nn);

  for (int v = 1; v < G.nn; ++v) {
    P[v] = -1;
    K[v] = INF;
    insert(shortpath, (ItemType){v, K[v]});
  }

  K[0] = 0;
  insert(shortpath, (ItemType){0, K[0]});

  while (shortpath->size > 0) {
    ItemType node = removeMin(shortpath);
    int u = node.content;

    for (TNode *nod = G.adl[u]; nod; nod = nod->next) {
      if (nod->c < K[nod->v]) {
        K[nod->v] = nod->c;
        P[nod->v] = u;
        insert(shortpath, (ItemType){nod->v, K[nod->v]});
      }
    }
  }

  printf("\nEdge  Weight\n");
  for (int n = 1; n < G.nn; n++)
    printf("%d - %d\t%d\n", P[n], n, K[n]);

  free(P);
  free(K);
  freeQueue(shortpath);
}

/**
 * Removes an edge between v1 and v2.
 */
void removeEdgeList(TGraphL *G, int v1, int v2) {
  TNode **it = &(G->adl[v1]);
  while (*it && (*it)->v != v2)
    it = &((*it)->next);
  if (*it) {
    TNode *temp = *it;
    *it = (*it)->next;
    free(temp);
  }

  it = &(G->adl[v2]);
  while (*it && (*it)->v != v1)
    it = &((*it)->next);
  if (*it) {
    TNode *temp = *it;
    *it = (*it)->next;
    free(temp);
  }
}

/**
 * Removes all edges connected to a node v.
 */
void removeNodeList(TGraphL *G, int v) {
  while (G->adl[v])
    removeEdgeList(G, v, G->adl[v]->v);
}

/**
 * Frees the entire adjacency list.
 */
void destroyGraphAdjList(TGraphL *G) {
  if (!G)
    return;

  for (int i = 0; i < G->nn; i++) {
    TNode *it = G->adl[i];
    while (it) {
      TNode *temp = it;
      it = it->next;
      free(temp);
    }
  }
  free(G->adl);
}

int main() {
  int i, v1, v2, c;
  int V, E;
  TGraphL G;

  freopen("../data/graph.in", "r", stdin);
  scanf("%d %d", &V, &E);
  alloc_list(&G, V);

  for (i = 0; i < E; i++) {
    scanf("%d %d %d", &v1, &v2, &c);
    insert_edge_list(&G, v1, v2, c);
  }

  printf("\nAdjacency List:\n");
  for (i = 0; i < G.nn; i++) {
    printf("%d : ", i);
    for (TNode *t = G.adl[i]; t != NULL; t = t->next)
      printf("%d(%d) ", t->v, t->c);
    printf("\n");
  }

  dijkstra(G, 0);
  Prim(G);
  destroyGraphAdjList(&G);

  return 0;
}
