

#ifndef         __GRAPH_ADJ_H__
#define         __GRAPH_ADJ_H__

#include "vertex.h"

/* This is the proposed structure for the new graph object.
 * It will mean that it is a proper object and not an alias to a several 
 * pointer level deep structure. It will mean things that are inherently
 * related to the graph are contained in the structure meaning more advanced
 * manipulations can be performed on the structure */
typedef struct {
        Vertex* vertices;
        uint32_t count;
} __graph, *Graph;


/* Graph specific prototypes */
void DFS(Vertex v, Vertex* dfsOrder, uint32_t* s);
void linkVertices(Graph g, uint32_t** adjlist);
Graph initGraph(Vertex* vs, uint32_t n);
void freeGraphP(Vertex** gp, uint32_t n);
Vertex** DFSForrest(Graph g);
void reverseGraph(Graph g);
void printGraph(Graph g);
void sortGraph(Graph g);
void freeGraph(Graph g);

#endif
