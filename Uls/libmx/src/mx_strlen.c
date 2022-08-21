#include "../inc/libmx.h"

int mx_strlen(const char *s) {
    int i = 0;
    for (i = 0; s[i]; i++);
    return i;
}

