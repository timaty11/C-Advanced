#include "../inc/libmx.h"

void mx_printstr(const char *s) {
    int str_len = mx_strlen(s);
    for (int i = 0; i < str_len; i++) {
        write(1, &s[i], 1);
    }
}

