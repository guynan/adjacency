
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

#ifndef         __VERTEX_220_H__
#define         __VERTEX_220_H__

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>


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


/* Contains a distinguishing id (for human readable purposes), pointer
 * to an array of other vertices that this vertex is adjacent to, and
 * a count that keeps track of how many vertices are contained in the
 * array of adjacent vertices. The amount of vertices that are allocated
 * for are also stored in eletotal; read: element total */
typedef struct _vertex {
        uint32_t id;
        struct _vertex** adjacent;
        uint32_t count;
        struct _vertex** reversedBy;
        uint16_t visited;
        vertexmeta meta;
} __vertex, *Vertex, **Graph;


/* Vertex compilation unit function prototypes */
void linkVertices(Vertex* vertices, uint32_t** adjlist, uint32_t n);
void DFS(Vertex v, Vertex* dfsOrder, uint32_t* s);
int vertexCompare(const void* a, const void* b);
void insertReversedBy(Vertex v, Vertex adj);
Vertex initVertex(uint32_t vid, uint32_t n);
void removeAdjacent(Vertex v, Vertex adj);
void addAdjacent(Vertex v, Vertex adj);
Graph* DFSForrest(Graph g, uint32_t n);
void reverseGraph(Graph g, uint32_t n);
void freeGraphP(Graph* gp, uint32_t n);
uint32_t countAdjacencyList(Vertex v);
void printGraph(Graph g, uint32_t n);
int reversedBy(Vertex v, Vertex adj);
int isAdjacent(Vertex v, Vertex adj);
void sortGraph(Graph g, uint32_t n);
uint32_t degree(Vertex v, char f);
Vertex* initVertices(uint32_t n);
vertexmeta initVertexmeta(void);
void printAdjacent(Vertex v);
void reverseArcs(Vertex v);
void freeVertex(Vertex v);
void freeGraph(Graph g);
int isSink(Vertex v);


#endif

