#include <stdio.h>
#include <stdint.h>
#include "adjacency.h"


int main(int argc, char** argv);

int main(int argc, char** argv)
{
        (void) argc;
        (void) argv;


        uint32_t k = 1000000;

        Graph g = initGraph(NULL, k);
        Vertex* vs = initVertices(k, g);
        setVertices(g, vs);

        freeGraph(g);

        return 0;

}
