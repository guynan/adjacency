/* This compilation unit includes all the content that pertains to 
 * initialising and manipulating relationships betweeen vertices */

#include "reverselist.h"


int main(int argc, char** argv)
{
        (void) argc;
        (void) argv;

        Vertex v = initVertex(1, 10);
        Vertex x = initVertex(5, 10);
        Vertex r = initVertex(9, 10);
        addAdjacent(v, x);
        addAdjacent(v, r);
        printAdjacent(v);
        reverseArcs(v);
        printAdjacent(v);
        printAdjacent(x);
        printf("%"PRIu32"\n", containsVertex(r, v->adjacent));

//        printf("%"PRIu32"\n", ((v->adjacent)[v->count -1])->id );

        return 0;
}

/* This function breathes life into our vertex structure. We give it a 
 * unique vertex id, and pass in how many possible elements in the 
 * adjacency list for each vertex. The safest thing to do here is pass in
 * the total number of elements in the adjacency matrix as it could 
 * be at max adjacent to that many elements. We also keep track of 
 * whether or not the arc has been reversed in the past */
Vertex initVertex(uint32_t vid, uint32_t n)
{
        Vertex v = malloc(sizeof(Vertex));

        v->id = vid;
        v->adjacent = malloc(n * sizeof(Vertex));
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
        Vertex* arr = v->adjacent;
        for(uint32_t i = 0; i < v->count; i++){

                if(!arr) continue;

                Vertex adj = arr[i];

                /* Then we reverse */
                if(!(adj->reversed) && !containsVertex(v, adj->adjacent)){
                                addAdjacent(adj, v);
                                removeAdjacent(v, adj);
                                puts("hi");
                }

                arr++;

        }

        v->reversed = 1;

}

/* Checks if vertex v is in the list arr */
int containsVertex(Vertex v, Vertex* arr)
{
        while(*arr){
                if(v == *arr){
                        return 1;
                }
                arr++;
        }

        return 0;

}

/* This function adds the adjacent vertex `adj` to the adjacency list
 * of vertex v */
void removeAdjacent(Vertex v, Vertex adj)
{
        Vertex* tmp = v->adjacent;

        /* HOLD UP DO I KEEP COUNT THE SAME */

        while(*tmp){

                if(*tmp == adj){
                        tmp = NULL;
                }

                tmp++;

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
        printf("%"PRIu32": ", v->id);

        Vertex* tmp = v->adjacent;
        for(uint32_t i = 0; i < v->count; i++){
                if(!tmp) continue;
                printf("%"PRIu32" ", (tmp[i])->id);

        }

        printf("\n");

}

