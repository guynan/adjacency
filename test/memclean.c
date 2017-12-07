#include <stdio.h>
#include <stdint.h>
#include "adjacency.h"

int main(int argc, char** argv);





int main(int argc, char** argv)
{
        (void) argc;
        (void) argv;

        uint32_t n = 10000;

        Graph g = initGraph(NULL, n);
        Vertex* vs = initVertices(n, g);
        setVertices(g, vs);

        /* We now set up some garbage memory so that there is some in the
         * memory pool for use to pick up on subsequent allocations */
        for(uint32_t i = 0; i < 7; i++){
                Vertex* garbage = initVertices(n, g);

                for(uint32_t i = 0; i < n; i++){
                        freeVertex(garbage[i]);
                }

                free(garbage);

        }

        freeGraph(g);


}
