#include "libmx.h"

char *mx_strdup(const char *s1) {
    char *ds = malloc(mx_strlen(s1) + 1);

    if (ds == NULL)
        return NULL;

    mx_strcpy(ds, s1);
    return ds;
}
