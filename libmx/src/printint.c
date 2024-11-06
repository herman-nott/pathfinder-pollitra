#include "libmx.h"

void mx_printint(int n) {
    if (n == -2147483648) {
        mx_printstr("-2147483648");
        return;
    }

    int div = 1;
    int dig;

    if (n < 0) {
        mx_printchar('-');
        n *= -1;
    }
    while (n / div > 9) {
        div *= 10;
    }
    while (div > 0) {
        dig = (n / div) % 10;
        mx_printchar(dig + '0');
        div /= 10;
    }
}
