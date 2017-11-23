

#ifndef __ADJACENCY_EDGEWEIGHT__
#define __ADJACENCY_EDGEWEIGHT__

/* This definition allows for there to be a way of linking a weight to a link
 * between vertices */

#include "vertex.h"
#include <stdint.h>

typedef struct {
        uint32_t weight;
        Vertex adj;
} __edge, Edge*;

#endif
