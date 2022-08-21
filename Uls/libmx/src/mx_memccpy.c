#include "../inc/libmx.h"

void *mx_memccpy(void *restrict dst, const void *restrict src, int c, size_t n) {
	if (n <= 0) {
		return dst;
	}

	char *dst_temp = (char *)dst;
	char *src_temp = (char *)src;

	for (unsigned long i = 0; src_temp[i] != '\0' && i < n; i++) {
		dst_temp[i] = src_temp[i];
		if (src_temp[i] == c && c != 0) {
			return (dst_temp + i + 1);
		}
	}

	return NULL;
}

