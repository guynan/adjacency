
#ifndef __ADJACENCY_VERTEX__
#define __ADJACENCY_VERTEX__

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
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#include "defs.h"

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

#endif

