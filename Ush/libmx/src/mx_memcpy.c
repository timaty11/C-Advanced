#include "../inc/libmx.h"

void *mx_memcpy(void *restrict dst, const void *restrict src, size_t n) {
    if (n <= 0) {
        return dst;
    }

    char *dst_temp = (char *)dst;
    char *src_temp = (char *)src;

    for (unsigned long i = 0; (src_temp[i] != '\0' && i < n); i++) {
        dst_temp[i] = src_temp[i];
    }

    return dst;
}

