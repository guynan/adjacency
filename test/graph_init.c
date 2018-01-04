
#include <stdio.h>
#include "adjacency.h"


int main();
#define MAX 12000

int main()
{
        Graph g = initGraph();

        for(uint32_t i = 0; i < MAX; i++){
                Vertex v = initVertex(i, g);
                addVertex(g, v);
        }

        printGraph(g);

        freeGraph(g);

        return 0;

}

