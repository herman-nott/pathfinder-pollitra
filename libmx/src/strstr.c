#include "libmx.h"

char *mx_strstr(const char *haystack, const char *needle) {
    if (!haystack || !needle)
        return NULL;

    if (!*needle)
        return (char *)haystack;

    int needle_len = mx_strlen(needle);

    while (*haystack) {
        if (!mx_strncmp(haystack, needle, needle_len))
            return (char *)haystack;
        haystack++;
    }
    return NULL;
}
