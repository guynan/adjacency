
#include <stdlib.h>
#include <stdint.h>


#ifndef         __VERTEX_META_H__
#define         __VERTEX_META_H__


/* I have not decided upon whether this is the path that I would like to take,
 * though there is a lot of associated data that pertains to particular vertex.
 * This structure would be initialised whenever a variable is calculated for 
 * particularly expensive calculations, effectively caching the data so
 * subsequent calculations are more rapid. It will by default not be
 * initialised so to initially speed up the setup of the Vertex structure and
 * not compromise the complexity if you are only dealing with very simple graph
 * problems. This will probably include data such as the in degree, out degree,
 * density, order and I will probably eschew the reversed by and visited
 * attributes from the vertex structure as they are pretty niche. */
typedef struct {
        uint32_t inDegree;
        uint32_t outDegree;
        double density;
} __vertexmeta__, *vertexmeta;


/* The graph object will initialise this field by default if the size of the 
 * graph is over a certain limit as a useful caching feature. Else the graph
 * will be small enough that the benefit would be immaterial */


/* Function Prototypes */
vertexmeta initVertexmeta(void);

#endif
