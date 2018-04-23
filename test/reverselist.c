/* This compilation unit takes a test file defined by FILE_PATH,
 * reads that into an adjacency list, which is then used to link the vertex
 * structures to form the graph. The graph is then reversed, sorted and written
 * to the file that is defined by FILE_OUT */

#include "adjacency.h"

#define LINE_SIZE               128
#define FILE_PATH               "data/list.txt"
#define FILE_OUT                "./reverselist.txt"

int main(int argc, char** argv);


int main(int argc, char** argv)
{
        (void) argc;
        (void) argv;

        uint32_t** adjlist = parseFile(FILE_PATH, LINE_SIZE);

        uint32_t count = countAdjList(adjlist);

        Graph g = initGraph();
        createVertices(g, count);

        linkVertices(g, adjlist);
        freeAdjacencyList(adjlist);
        printGraph(g);
        reverseGraph(g);
        sortGraph(g);

        writeAdjacencyList(g, FILE_OUT);

        freeGraph(g);

        return 0;
}


