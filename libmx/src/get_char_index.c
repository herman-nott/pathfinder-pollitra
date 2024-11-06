#include "libmx.h"

int mx_get_char_index(const char *str, char c) {
    if (str == NULL)
        return -2;
    int length = mx_strlen(str);

    for (int i = 0; i < length; i++) {
        if (str[i] == c)
            return i;
    }
    return -1;
}
