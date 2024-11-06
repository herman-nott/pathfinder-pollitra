#include "libmx.h"

bool mx_is_space(char c) {
    return (c == ' ' || c == '\t' || c == '\n'
            || c == '\v' || c == '\f' || c == '\r');
}
