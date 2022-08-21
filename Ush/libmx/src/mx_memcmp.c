#include "../inc/libmx.h"

int mx_memcmp(const void *s1, const void *s2, size_t n) {
    char *s1_temp = (char *)s1;
    char *s2_temp = (char *)s2;

    for (unsigned long i = 0; i < n; i++) {
        if (s1_temp[i] != s2_temp[i]) {
            return s1_temp[i] - s2_temp[i];
        }
    }

    return 0;
}

