#include "libmx.h"

void *mx_realloc(void *ptr, size_t size) {
    if (size <= 0) {
        free(ptr);
        return NULL;
    }
    if (!ptr && size)
        return malloc(size);

    size_t old_size = malloc_usable_size(ptr);
    size_t copy_size = 0;
    void *relloc_ptr = malloc(size);

    if (!relloc_ptr)
        return NULL;

    copy_size = old_size < size ? old_size : size;
    mx_memmove(relloc_ptr, ptr, copy_size);

    free(ptr);
    return relloc_ptr;
}
