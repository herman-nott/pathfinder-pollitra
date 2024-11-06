#include "libmx.h"

int mx_file_len(const char *file) {
    int fl = open(file, O_RDONLY);

    if (fl == -1)
        return -1;

    int temp;
    int len = 0;
    char c;

    while ((temp = read(fl, &c, 1)) > 0) {
        len++;
    }
    close(fl);
    return len;
}

