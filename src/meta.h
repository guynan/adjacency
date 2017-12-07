
#ifndef         __ADJACENCY_VERTEX_META__
#define         __ADJACENCY_VERTEX_META__

/* The graph object will initialise this field by default if the size of the 
 * graph is over a certain limit as a useful caching feature. Else the graph
 * will be small enough that the benefit would be immaterial */

#include <stdlib.h>
#include <stdint.h>

#include "defs.h"


/* Function Prototypes */
vertexmeta initVertexmeta(void);


#endif
