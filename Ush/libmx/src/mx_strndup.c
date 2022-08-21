#include "../inc/libmx.h"

char *mx_strndup(const char *s1, size_t n) {
    if (s1 == NULL) {
        return NULL;
    }
    char *dest = mx_strnew(n);
    dest = mx_strncpy(dest, s1, n);

    return dest;
}

