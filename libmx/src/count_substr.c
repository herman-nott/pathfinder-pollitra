#include "libmx.h"

int mx_count_substr(const char *str, const char *sub) {
    if (!str || !sub)
        return -1;

    if (mx_strlen(sub) == 0)
        return 0;

    int count = 0;
    int sub_len = mx_strlen(sub);

    while ((str = mx_strstr(str, sub)) != NULL) {
            count++;
            str += sub_len;
    }
    return count;
}
