
#include "adjacency.h"


Graph initGraph(void)
{
        Graph g = calloc(1, sizeof(struct _graph));

        if(!g)
                return NULL;

        g->vertices = NULL;
        g->order = 0;
        g->capacity = 0;

        /* Somewhat redundant since we calloc the graph in the first place,
         * but hey, explicit is better than implicit, right? */
        memset(&g->flags, 0, sizeof(struct _gflags));

        return g;

}


void printGraph(Graph g)
{
        if(!g || !g->vertices)
                return;

        Vertex* tmp = g->vertices;
        
        for(uint32_t i = 0; i < g->order; i++){
                if(!tmp[i])
                        continue;

                printAdjacent(tmp[i]);

        }

        return;

}


/* We initially iterate over the graph and reverse all the arcs in it. After
 * this, we reset all the reversedBy arrays to NULL such that subsequent 
 * reversals will not be polluted by the previous. Note that this is inplace */
void reverseGraph(Graph g)
{
        if(!g)
                return;
         
        Vertex* vs = g->vertices;

        if(!g->flags.REVERSED){
                for(uint32_t i = 0; i < g->order; i++){
                        __verticesrealloc(&vs[i]->reversedBy, &vs[i]->revlen, 
                                        g->order);
                }
        }

        g->flags.REVERSED = 1;

        for(uint32_t i = 0; i < g->order; i++){
                if(!vs[i]) continue;
                reverseArcs(vs[i]);
        }

        /* Make the graph reversible again */
        for(uint32_t i = 0; i < g->order; i++){
                if(!vs[i]) continue;

                Vertex v = vs[i];
                for(uint32_t j = 0; j < v->revlen; j++){
                        v->reversedBy[j] = NULL;
                }
        }

        return;

}


/* Takes a graph object and frees the vertices by calling freeVertex */
void freeGraph(Graph g)
{
        if(!g || !g->vertices)
                return;

        for(uint32_t i = 0; i < g->capacity; i++){
                freeVertex(g->vertices[i]);
        }

        free(g->vertices);

        free(g);
}


/* Should be distinguished from the freeGraph function as it does *not* free
 * and vertices that have been inserted into this structure. */
void freeGraphP(Vertex** gp, uint32_t n)
{
        /* Revise this strucure */
        return;
        Vertex** tmp  = gp;

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
        if(!g)
                return;

        uint32_t n = g->order;

        Vertex* vs = g->vertices;

        for(uint32_t i = 0; i < n; i++){
                Vertex a = vs[i];

                if(!vs[i])
                        continue;

                qsort(a->adjacent, a->count, sizeof(Vertex), vertexCompare);
        }

        return;

}


/* This function takes a graph and explores all the sub graphs in the dfs
 * forest, and returning the order in which they are visited */
Vertex** DFSForrest(Graph g)
{

        if(!g || !g->vertices)
                return NULL;

        Vertex** forrestOrder = calloc(g->order, sizeof(Vertex*));

        Vertex* vs = g->vertices;
        /* This should run once for each forrest */
        for(uint32_t i = 0; i < g->order; i++){

                if(vs[i]->flags.VISITED) continue;

                Vertex* dfsOrder = calloc((g->order + 1), sizeof(Vertex));

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

        v->flags.VISITED = 1;

        Vertex* adjacent = v->adjacent;
        for(uint32_t i = 0; i < v->count; i++){
                if(!adjacent[i]) continue;

                if(!(adjacent[i]->flags.VISITED)){
                        DFS(adjacent[i], dfsOrder, s);
                }
        }
        
        /* Once it gets to here we know that all of the adjacent
         * nodes have completed and we thusly `pop` the Vertex by 
         * writing it to the file */

        dfsOrder[(*s)++] = v;
        
}


/* This is an unforgiving operation; if you have a graph with an allocated set
 * of vertices, then this will go and free all resources associated with those
 * vertices, and update it with the new block that have been designated. */
void setVertices(Graph g, Vertex* vs, uint32_t n)
{
        if(g){
                if(g->vertices){
                        freeVertices(g->vertices, g->capacity);
                }

                g->vertices = vs;
                g->capacity = n;
                g->order = n;
        }

        return;
}


/* Links the `n` vertices according to the adjacency list provided */
void linkVertices(Graph g, uint32_t** adjlist)
{
        uint32_t n = g->order;
        Vertex* vs = g->vertices;

        for(uint32_t i = 0; i < n; i++){

                uint32_t* line = adjlist[i];
                for(uint32_t j = 0; j < n; j++){
                        if(!line[j]) break;

                        /* To understand this hack see initVertex */
                        if(line[j] == (uint32_t) -1) line[j] = 0;
                        addAdjacent(vs[i], vs[line[j]]);
                }
        }

        return;
}


/* Add a vertex to the graph, allocating more space if necessary and inserting
 * into an empty spot. */
void addVertex(Graph g, Vertex v)
{
        /* If there is no vertex, we would search for a slot and insert it.
         * better to reject it now and be done with it. */
        if(!g || !v)
                return;

        /* If the graph is empty at the moment, initialise storage space */
        if(!g->vertices || g->flags.GRAPH_FULL){
                __graph_realloc(&g->vertices, &g->capacity, g->order);
                g->flags.GRAPH_FULL = 0;
        }

        uint32_t i = 0;

        /* Assume that the last vertex is at the `order` slot but because there
         * are removals etc, this is not guaranteed and so we iterate until we
         * find an empty space, while setting hard boundary of the capacity */
        for(i = g->order; i < g->capacity; i++){
                if(!g->vertices[i]){
                        (g->vertices)[i] = v;
                        break;
                }
        }


        /* If almost full, make sure the next time we come around that we
         * allocate more space for subsequent insertions */
        if(i == g->capacity - 1){
                g->flags.GRAPH_FULL = 1;
        }
        
        g->order++;

        return;

}


/* This is a safer way of initialising n vertices and adding them to a graph.
 * The notion of allowing the user to create an array of vertices by however
 * means they see fit leads to the introduction of a lot of error. Since this
 * method is handled in a santised environment where the only input is the
 * graph and the number of vertices they would like to create, we can thusly
 * say categorically that we will know both the order and the capacity of the
 * graph with certainty. */
void createVertices(Graph g, uint32_t n)
{
        if(!g || !n)
                return;

        /* Destroy the old vertices if they exist */
        if(g->vertices){
                freeVertices(g->vertices, g->capacity);
        }

        Vertex* vs = initVertices(n, g);

        if(!vs)
                return;

        g->vertices = vs;
        g->capacity = n;
        g->order = n;

        return;

}


/* As opposed to destroying the old vertices on the graph, this function
 * instead generates the new vertices and then *adds* them to the current
 * graph, thereby preserving the old ones, and adding n vertices to g */
void addVertices(Graph g, uint32_t n)
{
        if(!g || !n)
                return;

        if(!g->vertices){
                createVertices(g, n);
                return;
        }

        for(u32 i = 0; i < n; i++){

                /* Create the new vertex and subsequently add it to g */
                Vertex v = initVertex(i, g);
                addVertex(g, v);
        }

        return;

}

