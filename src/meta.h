
#ifndef         __ADJACENCY_VERTEX_META__
#define         __ADJACENCY_VERTEX_META__

/* The graph object will initialise this field by default if the size of the 
 * graph is over a certain limit as a useful caching feature. Else the graph
 * will be small enough that the benefit would be immaterial */

#include <stdlib.h>
#include <stdint.h>

#include "defs.h"

#define META_INCR_IN_DEG(v)             v->meta->inDegree++
#define META_DECR_IN_DEG(v)             v->meta->inDegree--

#define META_INCR_OUT_DEG(v)            v->meta->outDegree++
#define META_DECR_OUT_DEG(v)            v->meta->outDegree--

/* Use this to first check whether meta has been initialised, and then whether
 * or not the particular field has been calculated prior to this */
#define META_FIELD_EXISTS(v, x)         v->meta && v->meta->x


/* Function Prototypes */
vertexmeta initVertexmeta(void);


#endif
