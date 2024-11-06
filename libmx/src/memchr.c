#include "libmx.h"

void *mx_memchr(const void *s, int c, size_t n) {
    const unsigned char *sp = (const unsigned char *)s;
    unsigned char uc = (unsigned char)c;

    for (size_t i = 0; i < n; i++) {
        if (sp[i] ==  uc)
            return (void *)(sp + i);
    }
    return NULL;
}
