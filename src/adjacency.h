#ifndef         __ADJACENCY_MASTER_ADJACENCY__
#define         __ADJACENCY_MASTER_ADJACENCY__


/*
 * This file is to streamline the structure defintions. There are a lot of
 * codependent structures and this ensures that if one is to granularly define
 * one header out of the adjacency module, there are no undefined references to
 * structures which often pass silently.
 */

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>


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
struct _vertexmeta {
        uint32_t                inDegree;
        uint32_t                outDegree;
        float                   density;
        struct _mflags          flags;
};


/* Contains a distinguishing id (for human readable purposes), pointer
 * to an array of other vertices that this vertex is adjacent to, and
 * a count that keeps track of how many vertices are contained in the
 * array of adjacent vertices. The amount of vertices that are allocated
 * for are also stored in eletotal; read: element total */
struct _vertex {
        struct _vertex**        adjacent;
        struct _graph*          graph;
        struct _vertex**        reversedBy;
        struct _vertexmeta*     meta;
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


/* Tyepdefs for userspace usage */
typedef struct _vertex*         Vertex;
typedef struct _vertexmeta*     vertexmeta;
typedef struct _graph*          Graph;


/* Typedefs for convenience */
typedef uint8_t                 u8;
typedef uint16_t                u16;
typedef uint32_t                u32;
typedef uint64_t                u64;

typedef int8_t                  s8;
typedef int16_t                 s16;
typedef int32_t                 s32;
typedef int64_t                 s64;


/* Define the `EMPTY_GRAPH`; all vertices that are not initialised to a graph
 * will all have this graph as the parent. Is later defined in vertex.c */
#if !defined __EMPTY_GRAPH_CONSTANT__
#define __EMPTY_GRAPH_CONSTANT__
extern struct _graph            EMPTY_GRAPH_STRUCT;
#endif

/* The graph object will initialise this field by default if the size of the
 * graph is over a certain limit as a useful caching feature. Else the graph
 * will be small enough that the benefit would be immaterial */


#define META_INCR_IN_DEG(v)             v->meta->inDegree++
#define META_DECR_IN_DEG(v)             v->meta->inDegree--

#define META_INCR_OUT_DEG(v)            v->meta->outDegree++
#define META_DECR_OUT_DEG(v)            v->meta->outDegree--

/* Use this to first check whether meta has been initialised, and then whether
 * or not the particular field has been calculated prior to this */
#define META_FIELD_EXISTS(v, x)         v->meta && v->meta->x


/* Function Prototypes */
vertexmeta initVertexmeta(void);


/* Note: This has been purposely over-engineered. I liked the idea of
 * structures in memory and the idea that pointers between them formed the arcs
 * of the graph. Though in saying that, there is machinery here that would be
 * evident by default in other programming languages and also design decisions
 * that have been made to reflect the agnosticism of the platform this is to
 * run upon (no particular platform) and also as I enjoy projects like this. I
 * see it foreseeable that I will indeed build upon this in future and in that
 * notion there are some things that have been done in such a way that it is
 * easily extensible and also robust with respect to the logical foundations of
 * graph theory. I decided upon the structure based design pattern as once one
 * gets over the initial hurdle of reading these data into the structure, the
 * pointer takes up no more room than a 64 bit integer meaning manipulating
 * these complex structures is not a great processing hardship. */


/* Vertex compilation unit function prototypes */
uint32_t countvertices(Vertex* vs, uint32_t max);
int vertexCompare(const void* a, const void* b);
void insertReversedBy(Vertex v, Vertex adj);
void removeAdjacent(Vertex v, Vertex adj);
void freeVertices(Vertex* vs, uint32_t n);
Vertex* initVertices(uint32_t n, Graph g);
Vertex initVertex(uint32_t vid, Graph g);
void addAdjacent(Vertex v, Vertex adj);
uint32_t countAdjacencyList(Vertex v);
int reversedBy(Vertex v, Vertex adj);
int isAdjacent(Vertex v, Vertex adj);
uint32_t degree(Vertex v, char f);
uint32_t getVertexId(Vertex v);
Vertex* getAdjacent(Vertex v);
void printAdjacent(Vertex v);
void reverseArcs(Vertex v);
void freeVertex(Vertex v);
int isSink(Vertex v);


/* Internal functions */
uint32_t _countindegree(Vertex v);

/* These macro expansions can (and should) be used to control how the order is
 * incremented and decremented */
#define GRAPH_ORDER_INCR(g)     g->order++
#define GRAPH_ORDER_DECR(g)     g->order--


/* Graph specific prototypes */
void DFS(Vertex v, Vertex* dfsOrder, uint32_t* s);
void setVertices(Graph g, Vertex* vs, uint32_t n);
void linkVertices(Graph g, uint32_t** adjlist);
void createVertices(Graph g, uint32_t n);
void freeGraphP(Vertex** gp, uint32_t n);
void addVertices(Graph g, uint32_t n);
void addVertex(Graph g, Vertex v);
Vertex** DFSForrest(Graph g);
void reverseGraph(Graph g);
void printGraph(Graph g);
void sortGraph(Graph g);
void freeGraph(Graph g);
Graph initGraph(void);


#define BASE            10
#define VERTICAL_LINES  56


void writeDFS(Vertex** tmp, const char* path, uint32_t n);
void writeAdjacencyList(Graph g, const char* path);
uint32_t** parseFile(const char* path, size_t ls);
uint32_t* readVertices(char* line, uint32_t ls);
void writeAdjacent(Vertex v, FILE* file);
uint32_t strtoint(char* s);

/*
typedef uint32_t** AdjList;
*/

void freeAdjacencyList(uint32_t** adjlist);
uint32_t countAdjList(uint32_t** adj);

/* This compilation unit defines all of the functions that control the
 * underlying behaviour of this library, mostly pertaining to initialisation,
 * reallocation, and also deallocation to ensure consistent memory management.
 * There are also some definitions that set the initial values for a lot of
 * properties which can be modified. */

/* Function prototypes */
void __verticesrealloc(Vertex** vsptr, uint32_t* currlen, uint32_t order);
void __graph_realloc(Vertex** vsptr, uint32_t* capacity, uint32_t order);
uint32_t __memprovisbs(uint32_t currlen, uint32_t order);
void __rm_empty_mem(Vertex* vs, uint32_t len);
void __memvacuum(Graph g, uint32_t opts);
void __reallocAdjacent(Vertex v);


/* Definitions */
#define FULL_VERT_THRESHOLD             10000
#define VERT_ADJACENT_SEGMENT           1000
#define VERT_ADJ_DENSITY                1
#define VERT_ADJ_PERCENT(order)         (VERT_ADJ_DENSITY * order) / 100
#define VERT_ADJ_ST_CAPACITY            16

#define MEM_SCALE_FACTOR                2

/* Memory vacuum options */
#define MEM_VAC_META_PURGE              0x1
#define MEM_VAC_MEM_COMPRESS            0x2
#define MEM_VAC_FULL_PURGE              0xFFFF

#define unlikely(x)                     (x)


#endif
