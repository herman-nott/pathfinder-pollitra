#include "libmx.h"

char *mx_itoa(int number) {
    if (number == 0)
        return mx_strdup("0");
    if (number == -2147483648)
        return mx_strdup("-2147483648");

    int len = mx_numlen(number);
    bool negativ = number < 0;
    char *str = mx_strnew(len);

    if (!str)
        return NULL;

    if (negativ) {
        str[0] = '-';
        number = -number;
    }
    while (number != 0) {
        str[--len] = (number % 10) + '0';
        number /= 10;
    }
    return str;
}
