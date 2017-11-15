

#ifndef __ADJACENCY_EDGEWEIGHT__
#define __ADJACENCY_EDGEWEIGHT__

#include "vertex.h"
#include <stdint.h>

typedef struct {
        uint32_t weight;
        Vertex adj;
} __edge, Edge*;

#endif
