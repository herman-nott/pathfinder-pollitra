#include "libmx.h"

unsigned long mx_hex_to_nbr(const char *hex) {
    if (!hex) return 0;

    unsigned long num = 0;

    while (*hex) {
        num *= 16;
        if (*hex >= 'a' && *hex <= 'f') {
            num += *hex - 'a' + 10;
        }
        else if (*hex >= 'A' && *hex <= 'F') {
            num += *hex - 'A' + 10;
        }
        else if (*hex >= '0' && *hex <= '9') {
            num += *hex - '0';
        }
        else {
            return 0;
        }
        hex++;
    }
    return num;
}
