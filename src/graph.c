#include "vertex.h"
#include "graph.h"

void printGraph(Graph g)
{
        Graph tmp = g;
        
        for(uint32_t i = 0; i < g->count; i++){
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

        if(!g->vertices)
                return;

        while(*(g->vertices)){
                freeVertex(*(g->vertices)++);
        }

        free(tmp);

}


/* Should be distinguished from the freeGraph function as it does *not* free
 * and vertices that have been inserted into this structure. */
void freeGraphP(Graph* gp, uint32_t n)
{
        /* Revise this strucure */
        return;
        Graph* tmp  = gp;

        if(!tmp) return;

        for(uint32_t i = 0; i < n; i++){
                if(!tmp[i]) continue;
                free(tmp[i]);
        }

        free(gp);

}


/* Sort the adjacency lists using a quicksort according to the id of vertex */
void sortGraph(Graph g)
{
        if(!g) return;
        uint32_t n = g->count;

        Vertex* vs = g->vertices;

        for(uint32_t i = 0; i < n; i++){
                Vertex a = vs[i];
                if(!vs[i]) continue;
                qsort(a->adjacent, a->count, sizeof(Vertex), vertexCompare);
        }

        return;

}


/* This function takes a graph and explores all the sub graphs in the dfs
 * forest, and returning the order in which they are visited */
Graph* DFSForrest(Graph g)
{

        Graph* forrestOrder = calloc(n, sizeof(Graph));

        Vertex* vs = g->vertices;
        /* This should run once for each forrest */
        for(uint32_t i = 0; i < g->count; i++){

                if(vs[i]->visited) continue;

                Vertex* dfsOrder = calloc(g->count, sizeof(Vertex));

                uint32_t k = 0;
                uint32_t* s = &k;

                DFS(vs[i], dfsOrder, s);

                forrestOrder[i] = dfsOrder;
        }

        return forrestOrder;

}


/* Pseudo code for DFS from Wikipedia  
 *
 *   procedure DFS(G,v):
 *       label v as discovered
 *       for all edges from v to w in G.adjacentEdges(v) do
 *           if vertex w is not labeled as discovered then
 *               recursively call DFS(G,w)
 *
 * Where G is a graph and v is a vertex index */
void DFS(Vertex v, Vertex* dfsOrder, uint32_t* s)
{
        if(!v) return;

        v->visited = 1;
        Vertex* adjacent = v->adjacent;
        for(uint32_t i = 0; i < v->count; i++){
                if(!adjacent[i]) continue;
                if(!adjacent[i]->visited){
                        DFS(adjacent[i], dfsOrder, s);
                }
        }
        
        /* Once it gets to here we know that all of the adjacent
         * nodes have completed and we thusly `pop` the Vertex by 
         * writing it to the file */

        dfsOrder[(*s)++] = v;
        
}


