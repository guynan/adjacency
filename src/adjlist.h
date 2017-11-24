
#ifndef __ADJACENCY_ADJLIST__
#define __ADJACENCY_ADJLIST__

#include <stdint.h>
#include <stdlib.h>

/*
typedef uint32_t** AdjList;
*/

void freeAdjacencyList(uint32_t** adjlist);
uint32_t countAdjList(uint32_t** adj);


#endif
