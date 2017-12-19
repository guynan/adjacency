
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
        memset(*vsptr + *currlen, 0, (newlen - *currlen) * sizeof(Vertex));

        *currlen = newlen;

        return;

}


/* This grows the graph structure as vertices are added. The thing to note here
 * is that the graph order must remain constant during the operation as it is
 * not the upper bound. In fact there is no upper bound, graphs can grow
 * arbitrarily large. */
void __graph_realloc(Vertex** vsptr, uint32_t* capacity, uint32_t order)
{
        void* tmp = NULL;

        uint32_t newcap = __memprovisbs(*capacity, order);

        tmp = realloc(*vsptr, (newcap * sizeof(Vertex)));

        /* Fuck */
        if(!tmp)
                return;

        *vsptr = tmp;

        memset(*vsptr + *capacity, 0, (newcap - *capacity) * sizeof(Vertex));

        *capacity = newcap;

        return;

}


/* Provision more memory and return the new block size */
uint32_t __memprovisbs(uint32_t currlen, uint32_t order)
{
        (void) order;

        return (!currlen) ? VERT_ADJ_ST_CAPACITY : currlen * 2;
}


void __initAdjacent(Vertex** vs_ptr, uint32_t* len, uint32_t n)
{
        void* tmp = NULL;

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


/* This is a potentially very time consuming exercise which *definitely*
 * operates in O(n^2) time. It Iterates over all structures that are included
 * in the graph structure and releases memory where it can. This works by */
void __memvacuum(Graph g, uint32_t opts)
{
        (void) g;
        (void) opts;

	return;
}


/* Pass this function a contiguous block of memory. The current length is
 * stored in `len` */
void __rm_empty_mem(Vertex* vs, uint32_t len)
{
	Vertex* src = vs;
	Vertex* dst = vs;

	uint32_t i;

	for(i = 0; i < len; i++){

		if (!src[i]){
			*dst = src[i];
			dst++;
		}
	}

	return;

}

