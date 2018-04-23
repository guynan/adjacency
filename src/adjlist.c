
#include "adjacency.h"

#include <stdlib.h>

/* Simply counts how many vertices are present in the adjacency list */
uint32_t countAdjList(uint32_t** adj)
{
        uint32_t** tmp = NULL;
        tmp = adj;
        uint32_t c = 0;

        while(tmp[c] != NULL){
                c++;
        }

        return c;
}


void freeAdjacencyList(uint32_t** adjlist)
{
        for(uint32_t i = 0; adjlist[i] != NULL; i++){
                free(adjlist[i]);
        }
                
        free(adjlist);

        return;
}

