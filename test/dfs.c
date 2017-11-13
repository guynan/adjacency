

#include "vertex.h"
#include "graph.h"

#define LINE_SIZE               128
#define FILE_PATH               "data/list.txt"
#define FILE_OUT                "./dfs.txt"

extern uint32_t** parseFile(const char* path, size_t ls);
extern void writeDFS(Graph* tmp, const char* path, uint32_t n);
void freeAdjacencyList(uint32_t** adjlist);
uint32_t countAdjList(uint32_t** adj);
int main(int argc, char** argv);


int main(int argc, char** argv)
{
        (void) argc;
        (void) argv;

        uint32_t** adjlist = parseFile(FILE_PATH, LINE_SIZE);

        uint32_t count = countAdjList(adjlist);

        Graph g = initVertices(count);
        sortGraph(g, count);

        linkVertices(g, adjlist, count);
        freeAdjacencyList(adjlist);
        
        Graph* dfs = DFSForrest(g, count);
        writeDFS(dfs, FILE_OUT, count);

        freeGraphP(dfs, count);
        freeGraph(g);


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


void freeAdjacencyList(uint32_t** adjlist)
{
        uint32_t** a = adjlist;
        while(*a) free(*a++);
                
        free(adjlist);

        return;

}


