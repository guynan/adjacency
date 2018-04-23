
#include <stdio.h>
#include "adjacency.h"


int main(int argc, char** argv);
#define MAX 12000

int main(int argc, char** argv)
{
        (void) argc;
        (void) argv;

        Graph g = initGraph();

        for(uint32_t i = 0; i < MAX; i++){
                Vertex v = initVertex(i, g);
                addVertex(g, v);
        }

        printGraph(g);

        freeGraph(g);

        return 0;

}

