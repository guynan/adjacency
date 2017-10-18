
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include "vertex.h"


#define LINE_SIZE               128
#define FILE_PATH               "./list.txt"
#define FILE_OUT                "out.txt"

int main(int argc, char** argv);

int main(int argc, char** argv)
{
        (void) argc;
        (void) argv;

        Vertex v = initVertex(1, 10);
        Vertex x = initVertex(5, 10);
        Vertex r = initVertex(9, 10);
        addAdjacent(v, x);
        addAdjacent(v, r);
        printAdjacent(v);
        reverseArcs(v);
        printAdjacent(v);
        printAdjacent(x);
        printAdjacent(r);
        reverseArcs(x);
        reverseArcs(r);

        printAdjacent(v);

//        printf("%"PRIu32"\n", ((v->adjacent)[v->count -1])->id );

        return 0;
}


