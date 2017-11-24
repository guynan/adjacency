/* This compilation unit includes all the content that pertains to 
 * initialising and manipulating relationships betweeen vertices */


#include "vertex.h"


/* This function breathes life into our vertex structure. We give it a 
 * unique vertex id, and pass in how many possible elements in the 
 * adjacency list for each vertex. The safest thing to do here is pass in
 * the total number of elements in the adjacency matrix as it could 
 * be at max adjacent to that many elements. We also keep track of 
 * whether or not the arc has been reversed in the past */
Vertex initVertex(uint32_t vid, uint32_t n)
{
        /* The following hack is such that we can distinguish between 
         * a value that is read from the file as 0, and also the 0 value
         * that the adjacency list is initialised to */
        if(vid == (uint32_t) -1) vid = 0;

        Vertex v = calloc(1, sizeof(__vertex));

        v->id = vid;
        v->adjacent = NULL;
        v->order = n;
        v->count = n;
        v->reversedBy = NULL;
        v->meta = NULL;

        memset(&v->flags, 0, sizeof(struct _vflags));

        __initAdjacent(&v->adjacent, &v->count, n);

        return v;

}


/* This is called when we have no more space left in the adjacency list and
 * (most importantly) the current length of the adjacency list of the vertex is
 * *not* equal to the order of the graph. Shouldn't get called too much */
void __reallocAdjacent(Vertex v)
{
        void* tmp = NULL;
        uint32_t new_len = (v->order / VERT_ADJACENT_SEGMENT);

        /* Don't assign the current length to be longer than order */
        v->count = (new_len < v->order) ? new_len : v->order;

        tmp = realloc(v->adjacent, (v->count * sizeof(Vertex)));

        /* Fuck */
        if(!tmp) return; 

        v->adjacent = tmp;

        return;

}


void __initAdjacent(Vertex** vs_ptr, uint32_t* len, uint32_t n)
{
        void* tmp = NULL;

        /* Improve handling of error transactions */
        /* The FULL VERT THRESHOLD is the amount that we deem to be small
         * enough so that we have an adjacency list that is capable of storing
         * a 100% filled adjacency list from the start. It has been done this
         * way as the memory overhead is negligible but the potential speed
         * benefits are tangible for dense, small graphs */
        if(n <= FULL_VERT_THRESHOLD){
                *len = n;
                tmp = calloc(*len, sizeof(Vertex));
                *vs_ptr = (tmp) ? tmp : NULL;
                return;
        }

        /* Initially allocate only segments of size VERT_ADJACENT_SEGMENT
         * meaning that the adjacency lists only are 100 * the inverse of the
         * segment size. For example, when $VAS = 5, that means it is optimised
         * for 20% filled adjacency lists from the start. If a particular
         * vertex requires more space than this, we realloc the vertex array on
         * the fly. This means that we arent allocating n^2 space.
         *
         * This in turn means that every transaction that deals with iterating
         * over the adjacency list of a vertex must be aware of the array size
         * and not the order of the graph. The list of each vertex will grow
         * not by a factor, but by the initial fraction of the order */

        *len = n / VERT_ADJACENT_SEGMENT;
        tmp = calloc(*len, sizeof(Vertex));
        *vs_ptr = (tmp) ? tmp : NULL;
        *len = n;

        return;

}


/* This function adds the adjacent vertex `adj` to the adjacency list
 * of vertex v */
void addAdjacent(Vertex v, Vertex adj)
{
        if(!v || !adj) return;

        for(uint32_t i = 0; i < v->count; i++){

                if(!(v->adjacent)[i]){
                        (v->adjacent)[i] = adj;
                        return;
                }
        }

        /* If we get here, this means that we have not inserted the vertex into
         * the adjacency list. In this case we need to check whether we need to
         * allocate some more space or do nothing */
        if(v->count == v->order) return;

        __reallocAdjacent(v);

        addAdjacent(v, adj);

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
        Vertex* tmp = v->adjacent;

        if(!v) return;

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


/* If you are lazy and want to initialise `n` vertices and have
 * them packaged nicely in an array for you, this is the function
 * for you! Returns a pointer to said array */
Vertex* initVertices(uint32_t n)
{
        Vertex* vert = calloc((n + 2), sizeof(Vertex));

        if(!vert) return NULL;

        /* A note on some of my design choices:
         *      This array starts at 1 as 0 is an invalid
         *      node name... Maybe? */

        for(uint32_t i = 0; i < n; i++){
               Vertex v = initVertex(i, n); 
               if(v) vert[i] = v;
        }

        return vert;

}


void __initReversedBy(Vertex v)
{
        void* b = calloc((v->count + 1), sizeof(Vertex));

        /* Do something */
        if(!b) return;

        v->reversedBy = b;

        return;
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
        if(f == 'o' || f == 'O'){

                /* Note here - if the vertex has 0 out degree, the count will
                 * always be updated. In my mind this is a bug */
                if(v->meta && v->meta->outDegree){
                        return v->meta->outDegree;
                }

                uint32_t c = countAdjacencyList(v);

                if(!v->meta) v->meta = initVertexmeta();
                v->meta->outDegree = c;

                return c;
        }

        /* Incomplete */

        return 0;

}


/* Takes the count of how many nodes are in the adjacency list of vertex v */
uint32_t countAdjacencyList(Vertex v)
{
        Vertex* adj = v->adjacent;

        if(adj){
               for(uint32_t i = 0; i < v->count; i++){
                       if(!adj[i]) return i;
                }
        }

        return 0;
}


Vertex* getAdjacent(Vertex v)
{
        return v->adjacent;
}


uint32_t getVertexId(Vertex v)
{
        return v->id;
}

