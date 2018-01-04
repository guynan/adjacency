#include <stdio.h>
#include <stdint.h>
#include "adjacency.h"


int main(int argc, char** argv);

int main(int argc, char** argv)
{
        (void) argc;
        (void) argv;


        uint32_t k = 1000000;

        Graph g = initGraph();
        createVertices(g, k);
        

        freeGraph(g);

        return 0;

}
