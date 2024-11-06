#include "libmx.h"

int mx_get_substr_index(const char *str, const char *sub) {
    if ((!str) || (!sub))
        return -2;
    char *result = mx_strstr(str, sub);

    if (result == NULL)
        return -1;
    return result - str;
}
