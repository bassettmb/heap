#include <string.h>

#include "heap.h"
#include "heapsort.h"

static inline int
memcmp_wrapper(void *context, const void *first, const void *second)
{
    return memcmp(first, second, *(size_t *)context);
}

/* Note: generic wrapper requires context be a pointer to a function pointer
 *       because the C standard dictates that function pointers not to
 *       castable to/from data pointers (e.g. void pointers). Passing a
 *       pointer to a function pointer allows the rule to be circumvented.
 * 
 * TODO: specialize for generic functions not expecting a context
 */
static inline int
generic_wrapper(void *context, const void *first, const void *second)
{
    return (*(int (**)(const void *, const void *))context)(first, second);
}

void
heapsort_default(void *base,
                 size_t nelem,
                 size_t elemsize,
                 int (*cmp)(const void *, const void *))
{
    struct heap target = { base, nelem, elemsize, generic_wrapper, &cmp };

    heap_rebuild(&target);
    heap_sort(&target);
}

void
heapsort_generic(void *base, size_t nelem, size_t elemsize)
{
    heapsort_context(base, nelem, elemsize, memcmp_wrapper, &elemsize);
}

void
heapsort_context(void *base,
                 size_t nelem,
                 size_t elemsize,
                 int (*cmp)(void *, const void *, const void *),
                 void *context)
{
    struct heap target = { base, nelem, elemsize, cmp, context };

    heap_rebuild(&target);
    heap_sort(&target);
}
