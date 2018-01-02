
#ifndef __ADJACENCY_DEFS__
#define __ADJACENCY_DEFS__

/* 
 * This file is to streamline the structure defintions. There are a lot of
 * codependent structures and this ensures that if one is to granularly define
 * one header out of the adjacency module, there are no undefined references to
 * structures which often pass silently. 
 */

#include <stdint.h>
#include <stddef.h>


/* The flag construction is so that we can store many boolean values in what is
 * the perfect array -- an unsigned integer. As we only need single bits to
 * register these values, below are the masks that make it easy to address
 * these in code. Supports 8 boolean values */
struct _vflags {
        uint8_t VISITED         : 1;
        uint8_t REVERSED        : 1;
        uint8_t FULL_ADJ        : 1;
        uint8_t                 : 1;
        uint8_t                 : 4;
};


/* The flag construction is so that we can store many boolean values in what is
 * the perfect array -- an unsigned integer. As we only need single bits to
 * register these values, below are the masks that make it easy to address
 * these in code. Supports 8 boolean values */
struct _gflags {
        uint8_t EMPTY           : 1;
        uint8_t REVERSED        : 1;
        uint8_t GRAPH_FULL      : 1;
        uint8_t                 : 1;
        uint8_t                 : 4;
};


/* This bit field provides flags to show whether cached values should be
 * recalculated or not. */
struct _mflags {
        uint8_t UPDATE_IN_DEG   : 1;
        uint8_t UPDATE_OUT_DEG  : 1;
        uint8_t                 : 6;
};


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
        float density;
        struct _mflags flags;
} __vertexmeta__, *vertexmeta;


/* Contains a distinguishing id (for human readable purposes), pointer
 * to an array of other vertices that this vertex is adjacent to, and
 * a count that keeps track of how many vertices are contained in the
 * array of adjacent vertices. The amount of vertices that are allocated
 * for are also stored in eletotal; read: element total */
struct _vertex {
        struct _vertex**        adjacent;
        struct _graph*          graph;
        struct _vertex**        reversedBy;
        vertexmeta              meta;
        uint32_t                id;
        uint32_t                count;
        uint32_t                revlen;
        struct _vflags          flags;
};


/* This is the proposed structure for the new graph object.
 * It will mean that it is a proper object and not an alias to a several 
 * pointer level deep structure. It will mean things that are inherently
 * related to the graph are contained in the structure meaning more advanced
 * manipulations can be performed on the structure */
struct _graph {
        struct _vertex**        vertices;
        uint32_t                order;
        uint32_t                capacity;
        struct _gflags          flags;
};


typedef struct _vertex*         Vertex;
typedef struct _graph*          Graph;


/* Define the `EMPTY_GRAPH`; all vertices that are not initialised to a graph
 * will all have this graph as the parent. Is later defined in vertex.c */
#if !defined __EMPTY_GRAPH_CONSTANT__
#define __EMPTY_GRAPH_CONSTANT__
extern struct _graph EMPTY_GRAPH_STRUCT;
#endif

#endif
