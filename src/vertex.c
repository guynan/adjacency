/* This compilation unit includes all the content that pertains to 
 * initialising and manipulating relationships betweeen vertices */


#include "adjacency.h"

#if !defined __EMPTY_GRAPH_CONSTANT__DEF

struct _graph EMPTY_GRAPH_STRUCT = {
        .vertices = NULL,
        .order = 0,

        .flags = {
                .EMPTY = 1,
                .REVERSED = 1,
        },
};

#define __EMPTY_GRAPH_CONSTANT__DEF
#endif

/* This function breathes life into our vertex structure. We give it a 
 * unique vertex id, and pass in how many possible elements in the 
 * adjacency list for each vertex. The safest thing to do here is pass in
 * the total number of elements in the adjacency matrix as it could 
 * be at max adjacent to that many elements. We also keep track of 
 * whether or not the arc has been reversed in the past */
Vertex initVertex(uint32_t vid, Graph g)
{
        /* The following hack is such that we can distinguish between 
         * a value that is read from the file as 0, and also the 0 value
         * that the adjacency list is initialised to */
        if(vid == (uint32_t) -1) vid = 0;

        Vertex v = calloc(1, sizeof(struct _vertex));

        if(!v)
                return NULL;

        v->id = vid;
        v->adjacent = NULL;
        v->count = 0;
        v->graph = (g) ? g : &EMPTY_GRAPH_STRUCT;
        v->reversedBy = NULL;
        v->revlen = 0;
        v->meta = NULL;

        memset(&v->flags, 0, sizeof(struct _vflags));

        __verticesrealloc(&v->adjacent, &v->count, v->graph->order);

        return v;

}


/* This function adds the adjacent vertex `adj` to the adjacency list
 * of vertex v */
void addAdjacent(Vertex v, Vertex adj)
{
        if(!v || !adj) return;

        Vertex* vs = v->adjacent;

        /* Check if the adjacency list is already full. */
        if(!vs || v->flags.FULL_ADJ){
                __verticesrealloc(&v->adjacent, &v->count, v->graph->order);
                v->flags.FULL_ADJ = 0;
        }


        for(uint32_t i = 0; i < v->count; i++){

                /* Means that now the container is full and will need to be
                 * resized probably */
                if(i == v->count - 1){
                        v->flags.FULL_ADJ = 1;
                }

                if(!(v->adjacent)[i]){

                        (v->adjacent)[i] = adj;

                        if(META_FIELD_EXISTS(v, outDegree))
                                META_INCR_OUT_DEG(v);

                        if(META_FIELD_EXISTS(adj, inDegree))
                                META_INCR_IN_DEG(adj);

                        return;
                }
        }

        return;

}


/* We reverse an arc when there is a directed arc pointing at one vertex
 * but the vertex does not return the love. 
 *
 * Improve nomenclature 
 *
 * for example:
 *
 * v ----> adj
 *
 * if adj is in v's adjacency list, we know too that there is an arc 
 * between the two at least. If in adj's adjacency list we find v, then
 * this implies:
 *
 * v <---> adj
 *
 * And in this case we do nothing. */
void reverseArcs(Vertex v)
{
        if(!v) return;

        Vertex* arr = (v->adjacent);

        for(uint32_t i = 0; i < v->count; i++){

                if(!arr[i]) continue;

                Vertex adj = arr[i];

                /* An arc is reversible either when neither are reversed
                 * or both are reversed. We can check this thusly: */
                if(!reversedBy(v, adj) && !isAdjacent(v, adj)){
                                addAdjacent(adj, v);
                                removeAdjacent(v, adj);
                                insertReversedBy(v, adj);

                }

        }


        return;
}


/* Checks if vertex v is in the adjacency list of adj */
int isAdjacent(Vertex v, Vertex adj)
{
        if(!v || !adj) return 0;

        Vertex* tmp = (adj->adjacent);

        for(uint32_t i = 0; i < adj->count; i++){

                if(v == tmp[i]) return 1;
        }

        return 0;

}


/* This function removes the adjacent vertex `adj` from the adjacency list
 * of vertex v */
void removeAdjacent(Vertex v, Vertex adj)
{
        if(!v) return;

        Vertex* tmp = (v->adjacent);

        for(uint32_t i = 0; i < v->count; i++){

                if(!tmp[i]){
                        continue;
                }

                if(tmp[i] == adj){
                        tmp[i] = NULL; 
                        return;
                }

        }

        return;

}


/* Simply prints the adjacency list of vertex v. Example output:
 *
 * 2: 3 5 6
 *
 * Which designates that vertex 2 (v) is adjacent to vertices 3, 5, 6 */
void printAdjacent(Vertex v)
{
        if(!v || !v->adjacent)
                return;
 
        Vertex* tmp = v->adjacent;

        printf("%"PRIu32": ", v->id);

        for(uint32_t i = 0; i < v->count; i++){

                if(!tmp[i]) continue;

                printf("%"PRIu32" ", (tmp[i])->id);

        }

        printf("\n");

}


/* Frees all resources associated with a Vertex */
void freeVertex(Vertex v)
{
        if(!v) return;

        if(v->reversedBy){
                free(v->reversedBy);
                v->reversedBy = NULL;
        }

        if(v->adjacent){
                free(v->adjacent);
                v->adjacent = NULL;
        }
        
        free(v);

        return;
}


/* Frees a container of vertices with the hard limit of the capacity */
void freeVertices(Vertex* vs, uint32_t n)
{
        for(u32 i = 0; i < n; i++){
                freeVertex(vs[i]);
        }

        free(vs);
}


/* If you are lazy and want to initialise `n` vertices and have
 * them packaged nicely in an array for you, this is the function
 * for you! Returns a pointer to said array */
Vertex* initVertices(uint32_t n, Graph g)
{
        Vertex* vert = calloc((n+1), sizeof(Vertex));

        if(!vert) return NULL;

        vert[n] = NULL;

        for(uint32_t i = 0; i < n; i++){
               Vertex v = initVertex(i, g); 
               if(v) vert[i] = v;
        }

        g->order = n;

        return vert;

}


/* Checks to see if the vertex v has reversed the arc between v and adj */
int reversedBy(Vertex v, Vertex adj)
{
        if(!v || !adj) return 0;

        Vertex* tmp = (adj->reversedBy);

        for(uint32_t i = 0; i < adj->count; i++){

                if(v == tmp[i]) return 1;
        }

        return 0;

}


/* Puts the vertex `adj` into the list of `reversedBy` for `v`. This is done
 * by a very simple check and insert manouvre. */
void insertReversedBy(Vertex v, Vertex adj)
{
        if(!v || !adj) return;

        Vertex* tmp = (v->reversedBy);

        for(uint32_t i = 0; i < v->count; i++){
                if(!tmp[i]){
                        tmp[i] = adj;
                        return;
                }

        }

        return;

}


/* This function is passed into the quicksort used to sort the adjacency lists
 * of the vertices. */
int vertexCompare(const void* a, const void* b)
{
        return (((Vertex) a)->id > ((Vertex) b)->id);
}


/* Checks if a vertex is a sink. This means that while other vertices may point
 * at the vertex, none must point out from the vertex. This is a convenient 
 * alias for asking for the out degree of the vertex is 0 */
int isSink(Vertex v)
{
       return (0 == degree(v, 'o'));
}


/* Here we pass in a conditional flag `f` which is a char which is either equal
 * to 'i' indicating we wish to assess the in degree of the vertex, or 'o'
 * which will indicate that we wish to assess the out degree. If an invalid
 * flag is returned or the vertex has no traversable resources. */
uint32_t degree(Vertex v, char f)
{
        uint32_t c = 0;

        if(!v || !f)
                return c;

        if(f == 'o' || f == 'O'){

                /* Note here - if the vertex has 0 out degree, the count will
                 * always be updated. In my mind this is a bug */
                if(META_FIELD_EXISTS(v, outDegree))
                        return v->meta->outDegree;

                c = countAdjacencyList(v);

                if(!v->meta)
                        v->meta = initVertexmeta();

                v->meta->outDegree = c;

                return c;
        }

        if(f == 'i' || f == 'I'){

                /* Note add a flag to see if recalculation is necessary */
                if(META_FIELD_EXISTS(v, inDegree))
                        return v->meta->inDegree;

                c = _countindegree(v);

                /* This, in particular is an expensive calculation, best to
                 * cache the result if we can */
                if(!v->meta)
                        v->meta = initVertexmeta();

                v->meta->inDegree = c;
        }

        return c;

}


/* This function should not be user visible - this is the machinery that is
 * used to count the indegree of the vertex, though we only want this to be
 * used when necessary. Results from previous calculations should be cached in
 * the meta section. As it stands this is only really good for static graphs */
uint32_t _countindegree(Vertex v)
{
        uint32_t c = 0;

        Graph g = v->graph;

        for(uint32_t i = 0; i < g->order; i++){

                Vertex tmp = g->vertices[i];

                if(!tmp)
                        continue;

                for(uint32_t j = 0; j < tmp->count; j++){

                        if(!(tmp->adjacent) || !(tmp->adjacent)[j])
                                continue;

                        if((tmp->adjacent)[j] == v)
                                c++;
                }

        }

        return c;
}


/* Takes the count of how many nodes are in the adjacency list of vertex v */
uint32_t countAdjacencyList(Vertex v)
{
        return countvertices(v->adjacent, v->count);
}


/* Generic function to count vertices in whatever application */
uint32_t countvertices(Vertex* vs, uint32_t max)
{
        if(!vs)
                return 0;

        uint32_t c = 0;

        for(uint32_t i = 0; i < max; i++){

                if(vs[i])
                        c++;
        }

        return c;
}


Vertex* getAdjacent(Vertex v)
{
        return v->adjacent;
}


uint32_t getVertexId(Vertex v)
{
        return v->id;
}

