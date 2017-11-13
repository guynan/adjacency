
#include "vertex.h"

#ifndef         __GRAPH_ADJ_H__
#define         __GRAPH_ADJ_H__


/* This is the proposed structure for the new graph object.
 * It will mean that it is a proper object and not an alias to a several 
 * pointer level deep structure. It will mean things that are inherently
 * related to the graph are contained in the structure meaning more advanced
 * manipulations can be performed on the structure */
/*
typedef struct {
        Vertex* graph;
        uint32_t count;
} __graph, *Graph;
*/

void reverseGraph(Graph g, uint32_t n);
void freeGraphP(Graph* gp, uint32_t n);
void printGraph(Graph g, uint32_t n);
void sortGraph(Graph g, uint32_t n);
void freeGraph(Graph g);

#endif
