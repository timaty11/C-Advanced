#include "../inc/libmx.h"

char *mx_strdup(const char *str) {
    int size = mx_strlen(str);
    char *copy = mx_strnew(size);
    mx_strcpy(copy, str);
    return copy;
}

