

#ifndef         __VERTEX_220_H__
#define         __VERTEX_220_H__

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>


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
} __vertex, *Vertex, **Graph;


/* Vertex compilation unit function prototypes */
void linkVertices(Vertex* vertices, uint32_t** adjlist, uint32_t n);
int vertexCompare(const void* a, const void* b);
void insertReversedBy(Vertex v, Vertex adj);
Vertex initVertex(uint32_t vid, uint32_t n);
void removeAdjacent(Vertex v, Vertex adj);
void addAdjacent(Vertex v, Vertex adj);
void reverseGraph(Graph g, uint32_t n);
void printGraph(Graph g, uint32_t n);
int reversedBy(Vertex v, Vertex adj);
int isAdjacent(Vertex v, Vertex adj);
void sortGraph(Graph g, uint32_t n);
Vertex* initVertices(uint32_t n);
void printAdjacent(Vertex v);
void reverseArcs(Vertex v);
void freeVertex(Vertex v);
void freeGraph(Graph g);


#endif

