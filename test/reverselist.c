/* This compilation unit takes a test file defined by FILE_PATH,
 * reads that into an adjacency list, which is then used to link the vertex
 * structures to form the graph. The graph is then reversed, sorted and written
 * to the file that is defined by FILE_OUT */

#include "vertex.h"
#include "graph.h"
#include "fileutils.h"

#define LINE_SIZE               128
#define FILE_PATH               "data/list.txt"
#define FILE_OUT                "./reverselist.txt"

void freeAdjacencyList(uint32_t** adjlist);
uint32_t countAdjList(uint32_t** adj);
int main(int argc, char** argv);


int main(int argc, char** argv)
{
        (void) argc;
        (void) argv;

        uint32_t** adjlist = parseFile(FILE_PATH, LINE_SIZE);

        uint32_t count = countAdjList(adjlist);

        Vertex* vs = initVertices(count);
        Graph g = initGraph(vs, count);

        linkVertices(g, adjlist);
        freeAdjacencyList(adjlist);
        reverseGraph(g);
        sortGraph(g);

        writeAdjacencyList(g, FILE_OUT);

        freeGraph(g);

        return 0;
}


/* Simply counts how many vertices are present in the adjacency list */
uint32_t countAdjList(uint32_t** adj)
{
        uint32_t** tmp = adj;
        uint32_t c = 0;

        for( ; *tmp++; c++)
                ;

        return c;
}


void freeAdjacencyList(uint32_t** adjlist)
{
        uint32_t** a = adjlist;
        while(*a) free(*a++);
                
        free(adjlist);

        return;

}

