#ifndef HEAP_INTERNAL_H
#define HEAP_INTERNAL_H

#include <stddef.h>
#include <string.h>
#include "heap.h"

/* Internal routines used by the heap functions. */

static inline int
compare(struct heap *heap, const void *first, const void *second)
{
    return heap->order(heap->context, first, second);
}

static inline void
gen_swap(void *fst, void *snd, size_t nbytes)
{
    char scratch[nbytes];

    memcpy(scratch, fst, nbytes);
    memcpy(fst, snd, nbytes);
    memcpy(snd, scratch, nbytes);
}

static inline void
swap(const struct heap *heap, void *fst, void *snd)
{
    gen_swap(fst, snd, heap->elemsize);
}

static inline void *
offset(const struct heap *heap, size_t ix)
{
    return (void *)((const char *)(heap->base) + ix * heap->elemsize);
}

static inline void *
succ(const struct heap *heap, const void *elem)
{
    return (void *)((const char *)elem + heap->elemsize);
}

static inline void *
pred(const struct heap *heap, const void *elem)
{
    return (void *)((const char *)elem - heap->elemsize);
}

static inline size_t
parent(size_t ix)
{
    return (ix - 1) / 2;
}

static inline size_t
childl(size_t ix)
{
    return ix * 2 + 1;
}

static inline size_t
childr(size_t ix)
{
    return (ix + 1) * 2;
}

#endif /* !HEAP_INTERNAL_H */
