#include "libmx.h"

char *mx_strndup(const char *s1, size_t n) {
    size_t len = mx_strlen(s1);
    size_t copy_len = (n < len) ? n : len;
    char *ds = malloc(copy_len + 1);

    if (ds == NULL)
        return NULL;
    mx_strncpy(ds, s1, copy_len);
    ds[copy_len] = '\0';
    return ds;
}
