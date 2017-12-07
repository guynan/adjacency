
#include <stdio.h>
#include <stdint.h>
#include "adjacency.h"

void testblock(void* ptr, size_t width);
int main(int argc, char** argv);
void garbgen(uint32_t n);


int main(int argc, char** argv)
{
        (void) argc;
        (void) argv;

        uint32_t n = 1000000;

        /* We now set up some garbage memory so that there is some in the
         * memory pool for use to pick up on subsequent allocations */
        garbgen(n);

        Vertex v = initVertex(0, NULL);

        /* Force the reallocation of a single vertex multiple times.
         * NOTE: This is the function that we are testing */
        for(uint32_t i = 0; i < 9; i++){
                __verticesrealloc(&v->adjacent, &v->count, n);
        }

        /* Theoretically by this point there should be at least *some* garbage
         * in the adjacency list of this memory *if* we have not done our job
         * right. We now cast it to a char* so we can inspect each byte */
        testblock(v->adjacent, v->count * sizeof(Vertex));


}

/* Theoretically, if there is no delinquency in our initialisation of memory
 * there will be no output from here because it will simply print out \0
 * characters. Though - if there is a flaw, these bytes will be printed to the
 * screen */
void testblock(void* ptr, size_t width)
{
        char* arr_realloced = ptr;

        for(size_t i = 0; i < width; i++){
                printf("%c", arr_realloced[i]);
        }

        return;
}


/* Perform multiple, large allocations using malloc and then initialising them
 * to a character. If this output is detected, this means that on an allocation
 * after garbage has been generated, these pages will be handed to malloc */
void garbgen(uint32_t n)
{
        for(uint32_t i = 0; i < 30; i++){

                uint32_t* garbage = malloc(n * sizeof(uint32_t));

                for(uint32_t i = 0; i < n; i++){
                        garbage[i] = 'x';
                }

                free(garbage);

        }

}

