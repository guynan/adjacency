
#include "wgraph.h"


WGraph initWeighedtGraph(Edge* es, uint32_t n)
{
        
        WGraph wg = calloc(n, sizeof(__wgraph));

        if(!wg)
                return NULL;

        wg->edges = es;
        wg->order= n;

        return wg;

}


void reverseWGraph(Wgraph wg)
{

        Edge* es = wg->edges;

        for(uint32_t i = 0; i < g->order; i++){
                if(!vs[i]) continue;
                reverseArcs((vs[i])->);
        }

        /* Make the graph reversible again */
        for(uint32_t i = 0; i < g->order; i++){
                if(!vs[i]) continue;

                Vertex v = vs[i];
                for(uint32_t i = 0; i < v->count; i++){
                        v->reversedBy[i] = NULL;
                }
        }

        return;

}
