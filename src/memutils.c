
#include "memutils.h"


/* Here we construct a general purpose vertex pointer reallocation method. This
 * is designed so that it can be used in many situations where you need to
 * lengthen the array, assign it to the pointer to the array if it is
 * successful and update the current length of the array if the length changes.
 * It also goes along after the reallocation and NULL's out the newly allocated
 * slots so that we can rely on checking those slots won't be addressing old
 * memory. Note that the order is the upper bound and will not be modified */
void __verticesrealloc(Vertex** vsptr, uint32_t* currlen, uint32_t order)
{
        /* This means that it can be used as an initialisation function too. It
         * is likely that the initialisation method will be deprecated in
         * favour of this */
        if(order <= FULL_VERT_THRESHOLD){
                *currlen = order;
        }

        void* tmp = NULL;

        uint32_t newlen = __memprovisbs(*currlen, order);

        /* Don't assign the current length to be longer than order. */
        newlen = (newlen < order) ? newlen : order;
        tmp = realloc(*vsptr, (newlen * sizeof(Vertex)));

        /* Fuck */
        if(!tmp) return;

        *vsptr = tmp;
        
        /* Zero out other slots in memory that have been added */
        for(uint32_t i = *currlen; i < newlen; i++){
                (*vsptr)[i] = NULL;
        }

        *currlen = newlen;

        return;

}


/* Provision more memory and return the new block size */
uint32_t __memprovisbs(uint32_t currlen, uint32_t order)
{
        (void) order;

        /* Experiment with percentages or log *//*
        uint32_t newlen = *currlen + VERT_ADJ_PERCENT(order);
        */

        return (!currlen) ? VERT_ADJ_ST_CAPACITY : currlen * 2;
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

        return;

}


/* This is called when we have no more space left in the adjacency list and
 * (most importantly) the current length of the adjacency list of the vertex is
 * *not* equal to the order of the graph. Shouldn't get called too much */
void __reallocAdjacent(Vertex v)
{
        void* tmp = NULL;

        uint32_t old_len = v->count;
        uint32_t new_len = v->count + (v->graph->order / VERT_ADJACENT_SEGMENT);

        /* Don't assign the current length to be longer than order */
        v->count = (new_len < v->graph->order) ? new_len : v->graph->order;

        tmp = realloc(v->adjacent, (v->count * sizeof(Vertex)));

        /* Fuck */
        if(!tmp){
                v->count = old_len;
                return;
        }

        v->adjacent = tmp;
        
        /* Zero out other slots in memory that have been added */
        for(uint32_t i = old_len; i < v->count; i++){
                (v->adjacent)[i] = NULL;
        }

        return;

}


void __initReversedBy(Vertex v)
{
        /* Should also check whether or not it has been initialised before.
         * otherwise memory leaks are likely */

        void* b = NULL;

        /* Reversing is not a space efficient transaction unless one knows the
         * maximum inDegree. If you do know this, you can set the size to be
         * that. If we do not know the max indegree
         * 
         * Further optimisation could be to set the length of the reversedBy
         * array to the indegree per vertex. */
        b = calloc(v->graph->order, sizeof(Vertex));

        v->reversedBy = (b) ? b : NULL;

        return;
}


