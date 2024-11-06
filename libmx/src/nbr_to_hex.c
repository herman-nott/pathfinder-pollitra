#include "libmx.h"

char *mx_nbr_to_hex(unsigned long nbr) {
    unsigned long temp = nbr;
    int size = 0;
    char *num = NULL;
    int q = 0;

    if (nbr == 0) {
        num = mx_strnew(1);
        *num = '0';
        return num;
    }
    while (temp != 0){
        size++;
        temp /= 16;
    }
    num = mx_strnew(size);
    while (size > 0) {
        q = nbr % 16;
        if (q >= 10) {
            num[--size] = q + 87;
        }
        else {
            num[--size] = q + 48;
        }
        nbr /= 16;
    }
    return num;
}
