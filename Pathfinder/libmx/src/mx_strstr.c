#include "../inc/libmx.h"

char *mx_strstr(const char *haystack, const char *needle) {
    for (int count = 0; count < mx_strlen(haystack); count += 1) {
        char *temp = mx_strchr(haystack, haystack[0]);
        haystack += 1;
        if (mx_strncmp(temp, needle, mx_strlen(needle)) == 0) {
            return (char *)haystack;
        }
    }

    return NULL;
}

