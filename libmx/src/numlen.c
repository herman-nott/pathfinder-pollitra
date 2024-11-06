#include "libmx.h"

int mx_numlen(int number) {
    int len = 0;

    if (number <= 0)
        len = 1;

    while (number != 0) {
        len++;
        number /= 10;
    }
    return len;
}
