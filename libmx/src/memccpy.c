#include "libmx.h"

void *mx_memccpy(void *restrict dst, const void *restrict src, int c, size_t n) {
    if (dst == NULL || src == NULL || n == 0)
        return NULL;

    unsigned char uc = (unsigned char)c;
    unsigned char *d = (unsigned char *)dst;
    const unsigned char *s = (const unsigned char *)src;

    for (size_t i = 0; i < n; i++) {
        d[i] = s[i];
        if (s[i] == uc)
            return (void *)(d + i + 1);
    }
    return NULL;
}
