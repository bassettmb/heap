#ifndef HEAPSORT_H
#define HEAPSORT_H

#include <stddef.h>

void heapsort_default(void *base, size_t nelem, size_t elemsize,
                        int (*cmp)(const void *, const void *));

void heapsort_generic(void *base, size_t nelem, size_t elemsize);

void heapsort_context(void *base, size_t nelem, size_t elemsize,
        int (*cmp)(void *, const void *, const void *), void *context);

#endif /* !HEAPSORT_H */
