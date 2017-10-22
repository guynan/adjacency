

#include "vertex.h"

#define LINE_SIZE               128
#define FILE_PATH               "./list.txt"
#define FILE_OUT                "out.txt"
#define VERTICES                32

extern void writeAdjacencyList(Graph g, const char* path, uint32_t n);
extern uint32_t** parseFile(const char* path, size_t ls);
uint32_t countAdjList(uint32_t** adj);
int main(int argc, char** argv);


int main(int argc, char** argv)
{
        (void) argc;
        (void) argv;

        uint32_t** adjlist = parseFile(FILE_PATH, LINE_SIZE);

        /* This is redundant as number of vertices is taken care of in file
         * io stage. For dealing with larger files, fix that first */
//        uint32_t vert = VERTICES;

        uint32_t count = countAdjList(adjlist);

        Vertex* vert = initVertices(count);


        linkVertices(vert, adjlist, count);
        reverseGraph(vert, count);
        sortGraph(vert, count);
        printGraph(vert, count);
        writeAdjacencyList(vert, FILE_OUT, count);

        /* Incomplete free */
        free(adjlist);
 //       freeGraph(vert);

        return 0;
}

uint32_t countAdjList(uint32_t** adj)
{
        uint32_t** tmp = adj;
        uint32_t c = 0;

        for( ; *tmp++; c++)
                ;

        return c;
}

