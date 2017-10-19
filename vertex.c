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
        Vertex v = malloc(sizeof(__vertex));

        v->id = vid;
        v->adjacent = malloc((n + 1) * sizeof(Vertex));
        v->count = 0;
        v->eletotal = n;
        v->reversed = 0;

        return v;

}


/* This function adds the adjacent vertex `adj` to the adjacency list
 * of vertex v */
void addAdjacent(Vertex v, Vertex adj)
{
        /* Now that we have trivial edge cases out of the way... */
        if(v->count == v->eletotal){
                return;
        }
        
        (v->adjacent)[v->count] = adj;
        v->count++; 
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
 * And in this case we do nothing.
 *
 * */
void reverseArcs(Vertex v)
{
        Vertex* arr = (v->adjacent);

        for(uint32_t i = 0; i < v->count; i++){

                if(!arr[i]){ 
                        continue;
                }

                Vertex adj = arr[i];

                /* An arc is reversible either when neither are reversed
                 * or both are reversed. We can check this thusly: */
//                uint32_t rev = !(adj->reversed ^ v->reversed);
                uint32_t rev = !(v->reversed) || adj->reversed;

                /* Then we reverse */
                if(rev && !containsVertex(v, adj)){
                                addAdjacent(adj, v);
                                removeAdjacent(v, adj);
                }

        }

        v->reversed = !(v->reversed);

}


/* Checks if vertex v is in the adjacency list of adj */
int containsVertex(Vertex v, Vertex adj)
{
        Vertex* tmp = (adj->adjacent);

        for(uint32_t i = 0; i < adj->count; i++){

                if(v == tmp[i]){
                        return 1;
                }
        }

        return 0;

}


/* This function removes the adjacent vertex `adj` from the adjacency list
 * of vertex v */
void removeAdjacent(Vertex v, Vertex adj)
{
        Vertex* tmp = (v->adjacent);

        /* HOLD UP DO I KEEP COUNT THE SAME */

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

        printf("%"PRIu32": ", v->id);

        for(uint32_t i = 0; i < v->count; i++){

                if(!tmp[i]) continue;

                printf("%"PRIu32" ", (tmp[i])->id);

        }

        printf("\n");

}

void freeVertex(Vertex v)
{
        if(v && v->adjacent){
                free(v->adjacent);
                free(v);
        }
        
        return;
}


void freeGraph(Graph g)
{
        if(!g) return;

        while(*g){
                freeVertex(*g);
        }

        free(g);

}


/* If you are lazy and want to initialise `n` vertices and have
 * them packaged nicely in an array for you, this is the function
 * for you! Returns a pointer to said array */
Vertex* initVertices(uint32_t n)
{
        Vertex* vert = malloc((n + 2) * sizeof(Vertex));
        if(!vert) return NULL;

        /* A note on some of my design choices:
         *      This array starts at 1 as 0 is an invalid
         *      node name... Maybe? */
        for(uint32_t i = 1; i <= n; i++){
               vert[i] = initVertex(i, n + 1); 
        }

        return vert;

}

