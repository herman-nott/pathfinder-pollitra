#include "libmx.h"

char *mx_strtrim(const char *str) {
    if (str == NULL)
        return NULL;

    int end = mx_strlen(str) - 1;
    int start = 0;
    int len = 0;

    while (mx_is_space(str[start])) {
        start++;
    }
    while (mx_is_space(str[end])) {
        end--;
    }
    if (start > end)
        return mx_strdup("");

    len = end - start + 1;
    return mx_strndup(str + start, len);
}
