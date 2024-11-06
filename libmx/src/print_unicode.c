#include "libmx.h"

void mx_print_unicode(wchar_t c) {
    unsigned char utf8[4];
    int len = 0;

    if (c < 0x80) {
        utf8[0] = (c >> 0 & 0x7F) | 0x00;
        len = 1;
    }
    else if (c < 0x800) {
        utf8[0] = (c >> 6 & 0x1F) | 0xC0;
        utf8[1] = (c >> 0 & 0x3F) | 0x80;
        len = 2;
    }
    else if (c < 0x10000) {
        utf8[0] = (c >> 12 & 0x0F) | 0xE0;
        utf8[1] = (c >> 6 & 0x3F) | 0x80;
        utf8[2] = (c >> 0 & 0x3F) | 0x80;
        len = 3;
    }
    else if (c < 0x110000) {
        utf8[0] = (c >> 18 & 0x07) | 0xF0;
        utf8[1] = (c >> 12 & 0x3F) | 0x80;
        utf8[2] = (c >> 6 & 0x3F) | 0x80;
        utf8[3] = (c >> 0 & 0x3F) | 0x80;
        len = 4;
    }
    else {
        return;
    }
    write(1,utf8,len);
}
