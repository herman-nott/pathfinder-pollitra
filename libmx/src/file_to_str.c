#include "libmx.h"

char *mx_file_to_str(const char *file) {
    if (file == NULL)
        return NULL;
    int fl = open(file, O_RDONLY);

    if (fl < 0)
        return NULL;
    int len = mx_file_len(file);
    char *str = mx_strnew(len);

    if (str == NULL) {
        close(fl);
        return NULL;
    }
    if (read(fl, str, len) != len) {
        free(str);
        close(fl);
        return NULL;
    }
    close(fl);
    return str;
}
