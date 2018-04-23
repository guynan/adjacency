
#include "adjacency.h"

#include <stdlib.h>

/* This is a purposely barren initialisation, we want the memory for the more
 * sizeable elements to be allocated on the fly as opposed to allocating memory
 * long before it is needed, if it is even needed at all. */
vertexmeta initVertexmeta(void)
{
        vertexmeta vm = calloc(1, sizeof(struct _vertexmeta));

        if(!vm) return NULL;

        vm->inDegree = 0;
        vm->outDegree = 0;
        vm->density = 0.0;

        return vm;

}


