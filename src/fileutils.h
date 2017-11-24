
#ifndef         __ADJACENCY_FILEUTILS__
#define         __ADJACENCY_FILEUTILS__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>
#include "vertex.h"
#include "graph.h"


#define BASE            10
#define VERTICAL_LINES  32


void writeDFS(Vertex** tmp, const char* path, uint32_t n);
void writeAdjacencyList(Graph g, const char* path);
uint32_t** parseFile(const char* path, size_t ls);
uint32_t* readVertices(char* line, uint32_t ls);
void writeAdjacent(Vertex v, FILE* file);
uint32_t strtoint(char* s);



#endif
