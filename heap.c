#include <assert.h>
#include <string.h>

#include "heap.h"
#include "heap_internal.h"

/**
 * Bubbles an element of the heap upwards into a position where it satisfies
 * the max-heap property.
 */
void
heap_bubbleup(struct heap *heap, size_t ix)
{
    size_t pix;
    void *child, *p;

    assert(heap);

    if (heap->nelems < 2) return; /* nothing to bubble up */
    if (ix > heap->nelems) return; /* index is out of bounds */

    child = offset(heap, ix);
    pix = parent(ix);
    p = offset(heap, pix);

    /* repeat while we have elements out of place
     * and have not reached the root element
     */
    while (ix) {

        pix = parent(ix);
        p = offset(heap, pix);

        /* if a child and its parent satisfy the heap property, we are done */
        if (compare(heap, p, child) >= 0) return;

        /* otherwise, we need to reorder the two
         * and check the parent's parent
         */
        swap(heap, p, child);
        ix = pix;
        child = p;
    }

}

/**
 * Bubbles an element of the heap downwards into a position where it satisfies
 * the max-heap property.
 */
void
heap_bubbledown(struct heap *heap, size_t ix)
{
    void *elem, *child;
    size_t lim, last;

    assert(heap);

    if (heap->nelems < 2) return; /* nothing to bubble down */
    if (ix > heap->nelems) return; /* index is out of bounds */

    last = heap->nelems - 1;

    /* the limiting element is the last element with children and the
     * only element that may have fewer than two children
     */

    lim = parent(last);
    elem = offset(heap, ix);


    /* here we handle the traversal through
     * heap elements linked to children
     */
    while (ix < lim) {
        void *other;
        size_t cix;

        /* since we have not yet reached the limit element, we know that each
         * parent we encounter will have two children
         */

        cix = childl(ix);
        child = offset(heap, cix);
        other = succ(heap, child);


        /* we pick the greater child to ensure that this subheap will satisfy
         * the heap property after we rearrange its elements
         */

        if (compare(heap, child, other) < 0) {
            ++cix;
            child = other;
        }

        /* if we satisfy the heap property, we are done */
        if (compare(heap, elem, child) >= 0) return;

        /* otherwise, we reorder the element with its greater child
         * and continue restoring the heap property
         */
        swap(heap, elem, child);
        ix = cix;
        elem = child;
    }

    if (ix > lim) return; /* element has no child and is at its correct index */

    /* if we have not yet returned, we know our current element is the limiting
     * element and that the last element is a child of the limiting element
     */

    child = offset(heap, last);

    /* if nelems is odd, the final subtree has two children */
    if (heap->nelems & 1) {
        void *other;
        other = pred(heap, child);
        if (compare(heap, child, other) < 0)
            child = other;
    }

    /* to fully restore the heap property,
     * we swap this element into place and are done
     */
    if (compare(heap, elem, child) < 0)
        swap(heap, elem, child);
}

/**
 * Construct a heap from a contiguous group of elements packed into a heap
 * structure with no assumptions about the ordering of elements with respect
 * to other elements in \theta(n) time.
 */
void
heap_rebuild(struct heap *heap)
{
    size_t ix;

    assert(heap);

    /* A heap of zero or one elements vacuously satisfies its requirements. */
    if (heap->nelems < 2) return;

    /* Otherwise, we pick the last element with children and ensure the heap
     * is valid by restoring its property on each subtree
     */
    ix = parent(heap->nelems - 1);

    do
        heap_bubbledown(heap, ix);
    while (ix --);

}

/**
 * Unstably sort the elements in a heap based on the heap's comparison function
 * in \theta(n * log n) time.
 */
void
heap_sort(struct heap *heap)
{
    size_t ix, nelems;

    assert(heap);

    /* We assume there that the heap satisfies
     * the max-heap property before we begin.
     */

    /* A heap of zero or one elements is vacuously ordered. */
    if (heap->nelems < 2) return;

    /* We save the number of elements because we shrink the heap as the
     * sort progresses.
     */
    nelems = heap->nelems;

    /* While there exists more than one element the valid heap, we swap the
     * last element with the first and then restore the max-heap property.
     *
     * The first element is guaranteed to be the largest when the heap is valid.
     *
     * We continue this until only a single element remains and then we know
     * that elements are unstably sorted.
     */
    while (--heap->nelems) {
        swap(heap, heap->base, offset(heap, heap->nelems));
        heap_bubbledown(heap, 0);
    }

    heap->nelems = nelems;
}
