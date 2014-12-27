#include <limits.h>
#include "heap_debug.h"
#include "heap_debug_util.h"
#include "heap_internal.h"

/* Debugging routines used for checking heap sanity. */

void
heap_print(FILE *out, const struct heap *heap)
{
    size_t prev, ix;

    fprintf(out, "heap: {nelems: %zu, elemsize: %zu, "
                 "order: <fn>, context: %p, elems: ",
            heap->nelems, heap->elemsize, heap->context);

    hex_print_elems(out, " ", heap->base, heap->nelems, heap->elemsize);
    fputs(" }\n", out);
}

void
heap_debug_print(struct heap *heap)
{
    return heap_print(stderr, heap);
}

int
heap_node_sanity(struct heap *heap, size_t ix)
{
    void *elem;

    /* invalid index .. what? */
    if (ix >= heap->nelems) 
        return 0; 

    elem = offset(heap, ix);

    if (childl(ix) < heap->nelems &&
            compare(heap, elem, offset(heap, childl(ix))) < 0)
        return 0;

    if (childr(ix) < heap->nelems && 
            compare(heap, elem, offset(heap, childr(ix))) < 0)
        return 0;

    return 1;

}
 
int
heap_sanity(struct heap *heap)
{
    size_t ix;
    for (ix = 0; ix < heap->nelems; ++ix) {
        if (!heap_node_sanity(heap, ix))
            return 0;
    }

    return 1;
}
