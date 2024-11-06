#include "libmx.h"

int mx_count_words(const char *str, char c) {
    if (str == NULL)
        return -1;

    int count = 1;

    for (int i = 0; i < mx_strlen(str); i++) {
        if (str[i] == c && str[i - 1] && str[i + 1])
            count++;
    }
    return count;
}
