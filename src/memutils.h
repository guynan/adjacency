
#ifndef __ADJACENCY_MEMUTILS__
#define __ADJACENCY_MEMUTILS__

/* This compilation unit defines all of the functions that control the 
 * underlying behaviour of this library, mostly pertaining to initialisation,
 * reallocation, and also deallocation to ensure consistent memory management.
 * There are also some definitions that set the initial values for a lot of
 * properties which can be modified. */

#include "vertex.h"
#include "graph.h"

/* Function prototypes */
void __verticesrealloc(Vertex** vsptr, uint32_t* currlen, uint32_t order);
void __initAdjacent(Vertex** vs_ptr, uint32_t* len, uint32_t n);
uint32_t __memprovisbs(uint32_t currlen, uint32_t order);
void __reallocAdjacent(Vertex v);
void __initReversedBy(Vertex v);


/* Definitions */
#define FULL_VERT_THRESHOLD             10000
#define VERT_ADJACENT_SEGMENT           1000
#define VERT_ADJ_DENSITY                1
#define VERT_ADJ_PERCENT(order)         (VERT_ADJ_DENSITY * order) / 100
#define VERT_ADJ_ST_CAPACITY            16



#endif

