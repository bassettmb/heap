#ifndef HEAP_H
#define HEAP_H

#include <stddef.h>

struct heap {
    void *base;      /**< pointer to the base of the backing heap array */
    size_t nelems;   /**< number of elements in the heap array */
    size_t elemsize; /**< size of a heap element in bytes */
    int (*order)(void *,
                 const void *,
                 const void *); /**< function taking a context and two elements
                                     and returning 1 in the case that the first
                                     is greater, 0 in the case that they are
                                     equal and -1 in the case that the second
                                     is greater */
    void *context; /**< optional context passed to the order function */
};

/**
 * Bubbles an element of the heap upwards into a position where it satisfies
 * the max-heap property.
 *
 * @param heap heap with an element to be bubbled up
 * @param ix index referencing the element to be bubbled up
 * @post the element originally at ix cannot immediately be bubbled further
 *       upwards without violating the max-heap property
 */
void heap_bubbleup(struct heap *heap, size_t ix);

/**
 * Bubbles an element of the heap downwards into a position where it satisfies
 * the max-heap property.
 *
 * @param heap heap with an element to be bubbled down
 * @param ix index referencing the element to be bubbled down
 * @post the element originally at ix cannot immediately be bubbled further
 *       downwards without violating the max-heap property
 */
void heap_bubbledown(struct heap *heap, size_t ix);

/**
 * Construct a heap from a contiguous group of elements packed into a heap
 * structure with no assumptions about the ordering of elements with respect
 * to other elements in \theta(n) time.
 *
 * @param heap structure containing the invalid heap
 * @post the heap satisfies the max-heap property
 */
void heap_rebuild(struct heap *heap);

/**
* Unstably sort the elements in a heap based on the heap's comparison function
* in \theta(n * log n) time.
*
* @param heap heap to be sorted
* @pre the heap satisfies the max-heap property
* @post the elements in the heap are ordered with respect to its
*        comparison function
*/
void heap_sort(struct heap *heap);

#endif /* !HEAP_H */
