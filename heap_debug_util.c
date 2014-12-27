#include <limits.h>
#include "heap_debug_util.h"

#define HEX_BITS 4
#define HEX_SHIFT HEX_BITS
#define HEX_MASK 0xf
#define HEX_DIGITS (CHAR_BIT / HEX_BITS + (CHAR_BIT % HEX_BITS ? 1 : 0))

static const char hex_table[] = "0123456789abcdef";

static char *
hex_write_elem(char *dest, const unsigned char *elem, size_t elemsize)
{
    unsigned char value;
    size_t ix, byte;
    char *off;

    dest += HEX_DIGITS * elemsize;
    off = dest;
    for (ix = 0; ix < elemsize; ++ix) {
        value = elem[ix];
        for (byte = 0; byte < HEX_DIGITS; ++byte) {
            *--off = hex_table[value & HEX_MASK];
            value >>= HEX_BITS;
        }
    }

    return dest;
}

int
hex_print_elems(FILE *out, const char *delim,
                    const void *mem, size_t nelems, size_t elemsize)
{
    int ok;
    size_t ix, buflen, last;
    unsigned char value;
    const unsigned char *elem;

    elem = mem;

    /* 2 extra char for '0x' */
    buflen = 2 + HEX_DIGITS * elemsize;
    char buf[buflen];

    buf[0] = '0';
    buf[1] = 'x';

    hex_write_elem(buf + 2, elem, elemsize);
    ok = fwrite(buf, sizeof *buf, buflen, out) == buflen;
    while (ok && --nelems) {
        elem += elemsize;
        hex_write_elem(buf + 2, elem, elemsize);
        ok = fputs(delim, out) != EOF &&
                 fwrite(buf, sizeof *buf, buflen, out) == buflen;
    }

    return !ok;
}

int
hex_print_elem(FILE *out, const void *mem, size_t elemsize)
{
    return hex_print_elems(out, "test", mem, 1, elemsize);
}
