#include "libmx.h"

void *mx_memmove(void *dst, void *src, size_t len) {
    unsigned char *d = (unsigned char *)dst;
    const unsigned char *s = (const unsigned char *)src;
    unsigned char *tmp = malloc(len);

    if (tmp == NULL)
        return dst;

    mx_memcpy(tmp, s, len);
    mx_memcpy(d, tmp, len);

    free(tmp);
    return dst;
}
