#include "libmx.h"

char *mx_del_extra_spaces(const char *str) {
    if (str == NULL) return NULL;
    int j = 0;
    int i = 0;
    char *trim = mx_strtrim(str);

    if (trim == NULL) return NULL;
    char *s = mx_strnew(mx_strlen(trim));

    if (s == NULL) {
        mx_strdel(&trim);
        return NULL;
    }
    for (i = 0; trim[i] != '\0'; i++) {
        if (!mx_is_space(trim[i]))
            s[j++] = trim[i];
        else {
            s[j++] = ' ';
            while (mx_is_space(trim[i + 1])) i++;
        }
    }
    mx_strdel(&trim);
    return s;
}
