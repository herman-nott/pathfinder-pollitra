#include "libmx.h"

char **mx_strsplit(const char *s, char c) {
    if (!s) return NULL;

    int count = mx_count_words(s, c);
    char **arr = (char **)malloc((count + 1) *sizeof(char *));

    if (!arr) return NULL;

    int j = 0;
    int i = 0;
    int letters = 0;
    int start = 0;

    while(s[i]) {
        while (s[i] == c && s[i] != '\0') i++;
        start = i;

        while (s[i] != c && s[i] != '\0') {
            letters++;
            i++;
        }

        if (letters > 0) {
            arr[j++] = mx_strndup(s + start, letters);
            letters = 0;
        }
    }
    arr[j] = NULL;
    return arr;
}
