#include "libmx.h"

char *mx_replace_substr(const char *str, const char *sub, const char *replace) {
    if (!sub || !str || !replace)
        return NULL;

    int index_s = 0; //substr index
    int i = 0;
    int count = mx_count_substr(str, sub);
    char *new_str = mx_strnew(mx_strlen(str) + count * (mx_strlen(replace) - mx_strlen(sub)));

    if (count == 0)
        return mx_strdup(str);
    if (!new_str)
        return NULL;

    while (*str) {
        index_s = mx_get_substr_index(str, sub);
        if (index_s >= 0) {
            mx_strncpy(&new_str[i], str, index_s);
            i += index_s;
            mx_strcpy(&new_str[i], replace);
            i += mx_strlen(replace);
            str += index_s + mx_strlen(sub);
        }
        else {
            mx_strcpy(&new_str[i], str);
            break;
        }
    }
    return new_str;
}
