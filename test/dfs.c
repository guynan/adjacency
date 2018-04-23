

#include "adjacency.h"

#define LINE_SIZE               128
#define FILE_PATH               "data/list.txt"
#define FILE_OUT                "./dfs.txt"

extern uint32_t** parseFile(const char* path, size_t ls);
int main(int argc, char** argv);


int main(int argc, char** argv)
{
        (void) argc;
        (void) argv;

        uint32_t** adjlist = parseFile(FILE_PATH, LINE_SIZE);

        uint32_t count = countAdjList(adjlist);

        Graph g = initGraph();
        addVertices(g, count);

        linkVertices(g, adjlist);

        freeAdjacencyList(adjlist);

        Vertex** dfs = DFSForrest(g);
        writeDFS(dfs, FILE_OUT, count);

        freeGraphP(dfs, count);
        freeGraph(g);


        return 0;
}

