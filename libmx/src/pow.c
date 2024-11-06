#include "libmx.h"

double mx_pow(double n, unsigned int pow) {
    float num = 1.0;

    if (pow == 0)
        return 1.0;

    while (pow != 0) {
        num *= n;
        pow--;
    }
    return num;
}
