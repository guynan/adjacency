
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>


#define LINE_SIZE               128
#define FILE_PATH               "./list.txt"
#define FILE_OUT                "out.txt"


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
int containsVertex(Vertex v, Vertex adj);
void removeAdjacent(Vertex v, Vertex adj);
void addAdjacent(Vertex v, Vertex adj);
void printAdjacent(Vertex v);
void reverseArcs(Vertex v);


int main(int argc, char** argv);
