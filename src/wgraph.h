
#ifndef         __ADJACENCY_W_GRAPH__
#define         __ADJACENCY_W_GRAPH__

#include "edgeweight.h"
#include <stdint.h>

/* This allows the user to define a weighted graph. This functionality could
 * have been rolled into the graph object, though in that notion this means
 * that if you do want to initialise a weighted graph, you commit to allowing
 * for a slightly larger memory footprint */

typedef struct {
        Edge* edges;
        uint32_t order;
} __wgraph, *WGraph;

#endif
