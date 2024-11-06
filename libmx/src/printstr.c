#include "libmx.h"

void mx_printstr(const char *s) {
    if (s == NULL) {
        return;
    }
    while (*s) {
        mx_printchar(*s);
        s++;
    }
}
