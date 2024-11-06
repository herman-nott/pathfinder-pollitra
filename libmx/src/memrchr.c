#include "libmx.h"

void *mx_memrchr(const void *s, int c, size_t n) {
    const unsigned char *ptr = (const unsigned char *)s;
    unsigned char uc = (unsigned char)c;

    while (n > 0) {
        if (ptr[n - 1] == uc) {
            return (void *)(ptr + n - 1);
        }
        n--;
    }
    return NULL;
}
