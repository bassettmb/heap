#ifndef HEAP_DEBUG_UTIL_H
#define HEAP_DEBUG_UTIL_H

#include <stddef.h>
#include <stdio.h>

int hex_print_elems(FILE *out, const char *delim,
                    const void *mem, size_t nelems, size_t elemsize);

int hex_print_elem(FILE *out, const void *mem, size_t elemsize);

#endif /* !HEAP_DEBUG_UTIL_H */
