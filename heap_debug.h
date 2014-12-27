#ifndef HEAP_DEBUG_H
#define HEAP_DEBUG_H

#include <stddef.h>
#include <stdio.h>
#include "heap.h"

/* Debugging routines used for checking heap sanity. */

void heap_print(FILE *out, const struct heap *heap);
void heap_debug_print(struct heap *heap);
int heap_node_sanity(struct heap *heap, size_t ix);
int heap_sanity(struct heap *heap);

#endif /* !HEAP_DEBUG_H */
