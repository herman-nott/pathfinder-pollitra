#include "libmx.h"

void *mx_memmem(const void *big, size_t big_len, const void *little, size_t little_len) {
    if (big_len >= little_len && big_len > 0 && little_len > 0) {

        unsigned char *haystack = (unsigned char *)big;
        unsigned char *needle = (unsigned char *)little;

        for (size_t i = 0; i <= big_len - little_len; i++) {
            if (mx_memcmp(&haystack[i], needle, little_len) == 0)
                return (void *)&haystack[i];
        }
    }
    return NULL;
}
