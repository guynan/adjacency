
#ifndef         __ADJACENCY_VERTEX__
#define         __ADJACENCY_VERTEX__

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

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include "meta.h"


/* The flag construction is so that we can store many boolean values in what is
 * the perfect array -- an unsigned integer. As we only need single bits to
 * register these values, below are the masks that make it easy to address
 * these in code. Supports 8 boolean values */
struct _vflags {
        uint8_t VISITED         : 1;
        uint8_t REVERSED        : 1;
        uint8_t                 : 6;
};


/* Contains a distinguishing id (for human readable purposes), pointer
 * to an array of other vertices that this vertex is adjacent to, and
 * a count that keeps track of how many vertices are contained in the
 * array of adjacent vertices. The amount of vertices that are allocated
 * for are also stored in eletotal; read: element total */
typedef struct _vertex {
        uint32_t                id;
        struct _vertex**        adjacent;
        uint32_t                count;
        uint32_t                order;
        uint32_t                revlen;
        struct _vertex**        reversedBy;
        struct _vflags          flags;
        vertexmeta              meta;
} __vertex, *Vertex;



/* Vertex compilation unit function prototypes */
uint32_t countvertices(Vertex* vs, uint32_t max);
int vertexCompare(const void* a, const void* b);
void insertReversedBy(Vertex v, Vertex adj);
Vertex initVertex(uint32_t vid, uint32_t n);
void removeAdjacent(Vertex v, Vertex adj);
void addAdjacent(Vertex v, Vertex adj);
uint32_t countAdjacencyList(Vertex v);
int reversedBy(Vertex v, Vertex adj);
int isAdjacent(Vertex v, Vertex adj);
uint32_t degree(Vertex v, char f);
Vertex* initVertices(uint32_t n);
uint32_t getVertexId(Vertex v);
Vertex* getAdjacent(Vertex v);
void printAdjacent(Vertex v);
void reverseArcs(Vertex v);
void freeVertex(Vertex v);
int isSink(Vertex v);


#endif

