#include "libmx.h"

int mx_sqrt(int x) {
    if (x < 0 || x == 0) return 0;
    if (x == 1) return 1;

    int sqrtwb = 1;

    while (sqrtwb <= x / sqrtwb) {
        sqrtwb++;
    }
    sqrtwb--;
    if (sqrtwb * sqrtwb == x)
        return sqrtwb;
    else
        return 0;
}
