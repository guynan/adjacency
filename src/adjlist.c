
#include "adjlist.h"

/* Simply counts how many vertices are present in the adjacency list */
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

