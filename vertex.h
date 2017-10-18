

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
        uint32_t eletotal;
        uint16_t reversed;
} *Vertex;


/* Vertex compilation unit function prototypes */
Vertex initVertex(uint32_t vid, uint32_t n);
void removeAdjacent(Vertex v, Vertex adj);
int containsVertex(Vertex v, Vertex adj);
void addAdjacent(Vertex v, Vertex adj);
Vertex* initVertices(uint32_t n);
void printAdjacent(Vertex v);
void reverseArcs(Vertex v);
void freeVertex(Vertex v);


#endif

