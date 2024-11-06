#include "libmx.h"

char *mx_strntrim(const char *str, char c) {
    if (str == NULL)
        return NULL;

    int end = mx_strlen(str) - 1;
    int start = 0;
    int len = 0;

    while (str[start] == c && str[start] != '\0')
        start++;

    while (end >= start && str[end] == c)
        end--;

    if (start > end)
        return NULL;

    len = end - start + 1;

    return mx_strndup(str + start, len);
}
