#include "vertex.h"
#include "graph.h"

void printGraph(Graph g, uint32_t n)
{
        Graph tmp = g;
        
        for(uint32_t i = 0; i < n; i++){
                if(!tmp[i]) continue;

                printAdjacent(tmp[i]);

        }

        return;

}


/* We initially iterate over the graph and reverse all the arcs in it. After
 * this, we reset all the reversedBy arrays to NULL such that subsequent 
 * reversals will not be polluted by the previous. */
void reverseGraph(Graph g, uint32_t n)
{
        for(uint32_t i = 0; i < n; i++){
                if(!g[i]) continue;
                reverseArcs(g[i]);
        }

        /* Make the graph reversible again */
        for(uint32_t i = 0; i < n; i++){
                if(!g[i]) continue;

                Vertex v = g[i];
                for(uint32_t i = 0; i < v->count; i++){
                        v->reversedBy[i] = NULL;
                }
        }

        return;

}


/* Takes a graph object and frees the vertices by calling freeVertex */
void freeGraph(Graph g)
{
        Graph tmp = g;
        if(!g) return;

        while(*g){
                freeVertex(*g++);
        }

        free(tmp);

}


/* Should be distinguished from the freeGraph function as it does *not* free
 * and vertices that have been inserted into this structure. */
void freeGraphP(Graph* gp, uint32_t n)
{
        Graph* tmp  = gp;

        if(!tmp) return;

        for(uint32_t i = 0; i < n; i++){
                if(!tmp[i]) continue;
                free(tmp[i]);
        }

        free(gp);

}


/* Sort the adjacency lists using a quicksort according to the id of vertex */
void sortGraph(Graph g, uint32_t n)
{
        if(!g) return;

        for(uint32_t i = 0; i < n; i++){
                Vertex a = g[i];
                if(!g[i]) continue;
                qsort(a->adjacent, a->count, sizeof(Vertex), vertexCompare);
        }

        return;

}


