#include "libmx.h"

void *mx_memset(void *b, int c, size_t len) {
    unsigned char *pointer = (unsigned char *)b;
    size_t i = 0;

    while(i < len) {
        pointer[i] = (unsigned char)c;
        i++;
    }
    return b;
}
