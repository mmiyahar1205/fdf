#include "fdf.h"

void *ft_memcpy(void *dest, const void *src, size_t n) 
{
    unsigned char *d;
    const unsigned char *s;

    d = (unsigned char *)dest;
    s = (const unsigned char *)src;
    if (!d && !s)
        return NULL;
    while (n--)
        *d++ = *s++;
    return dest;
}
