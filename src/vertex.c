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
        v->adjacent = calloc((n + 1), sizeof(Vertex));
        v->count = n;
        v->reversedBy = calloc((n + 1), sizeof(Vertex));
        v->visited = 0;

        return v;

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


void printGraph(Graph g, uint32_t n)
{
        Graph tmp = g;
        
        for(uint32_t i = 0; i < n; i++){
                if(!tmp[i]) continue;

                printAdjacent(tmp[i]);

        }

        return;

}


/* Frees all resources associated with a Vertex */
void freeVertex(Vertex v)
{
        if(v && v->adjacent){
                free(v->reversedBy);
                free(v->adjacent);
                free(v);
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
               vert[i] = v;
        }

        return vert;

}


/* Links the `n` vertices according to the adjacency list provided */
void linkVertices(Vertex* vertices, uint32_t** adjlist, uint32_t n)
{
        for(uint32_t i = 0; i < n; i++){

                uint32_t* line = adjlist[i];
                for(uint32_t j = 0; j < n; j++){
                        if(!line[j]) break;

                        /* To understand this hack see initVertex */
                        if(line[j] == (uint32_t) -1) line[j] = 0;
                        addAdjacent(vertices[i], vertices[line[j]]);
                }
        }

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


/* This function is passed into the quicksort used to sort the adjacency lists
 * of the vertices. */
int vertexCompare(const void* a, const void* b)
{
        return (((Vertex) a)->id > ((Vertex) b)->id);
}


/* This function takes a graph and explores all the sub graphs in the dfs
 * forest, and returning the order in which they are visited */
Graph* DFSForrest(Graph g, uint32_t n)
{

        Graph* forrestOrder = calloc(n, sizeof(Graph));

        /* This should run once for each forrest */
        for(uint32_t i = 0; i < n; i++){

                if(g[i]->visited) continue;

                Vertex* dfsOrder = calloc(n, sizeof(Vertex));

                uint32_t k = 0;
                uint32_t* s = &k;

                DFS(g[i], dfsOrder, s);

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
                return countAdjacencyList(v);
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

