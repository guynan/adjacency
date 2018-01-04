
#ifndef __ADJACENCY_GRAPH__
#define __ADJACENCY_GRAPH__

#include <stdint.h>
#include <stdlib.h>

#include "defs.h"


/* These macro expansions can (and should) be used to control how the order is
 * incremented and decremented */
#define GRAPH_ORDER_INCR(g)     g->order++
#define GRAPH_ORDER_DECR(g)     g->order--


/* Graph specific prototypes */
void DFS(Vertex v, Vertex* dfsOrder, uint32_t* s);
void setVertices(Graph g, Vertex* vs, uint32_t n);
void linkVertices(Graph g, uint32_t** adjlist);
void createVertices(Graph g, uint32_t n);
void freeGraphP(Vertex** gp, uint32_t n);
void addVertices(Graph g, uint32_t n);
void addVertex(Graph g, Vertex v);
Vertex** DFSForrest(Graph g);
void reverseGraph(Graph g);
void printGraph(Graph g);
void sortGraph(Graph g);
void freeGraph(Graph g);
Graph initGraph(void);

#endif

