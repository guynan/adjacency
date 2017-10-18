

#include "vertex.h"

#define LINE_SIZE               128
#define FILE_PATH               "./list.txt"
#define FILE_OUT                "out.txt"
#define VERTICES                32

void linkVertices(Vertex* vertices, uint32_t** adjlist, uint32_t n);
uint32_t** parseFile(const char* path, size_t ls);
uint32_t countAdjList(uint32_t** adj);
int main(int argc, char** argv);


int main(int argc, char** argv)
{
        (void) argc;
        (void) argv;

        uint32_t** adjlist = parseFile(FILE_PATH, LINE_SIZE);

        puts("got here");
        /* This is redundant as number of vertices is taken care of in file
         * io stage. For dealing with larger files, fix that first */
//        uint32_t vert = VERTICES;

        uint32_t count = countAdjList(adjlist);

        Vertex* vertices = initVertices(count);
        linkVertices(vertices, adjlist, count);

//        free(adjlist);


//        printf("%"PRIu32"\n", ((v->adjacent)[v->count -1])->id );

        return 0;
}

uint32_t countAdjList(uint32_t** adj)
{
        uint32_t c;

        for( ; *adj++; c++)
                ;

        return c;
}


/* Links the `n` vertices according to the adjacency list provided */
void linkVertices(Vertex* vertices, uint32_t** adjlist, uint32_t n)
{
        for(uint32_t i = 1; i <= n; i++){
                uint32_t* line = adjlist[i - 1];
                for(uint32_t j = 0; j <= n; j++){
                        if(!line[j]) break;
                        addAdjacent(vertices[i], vertices[line[j]]);
                }
        }
        return;
}


