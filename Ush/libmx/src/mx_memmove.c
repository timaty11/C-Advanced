#include "../inc/libmx.h"

void *mx_memmove(void *dst, const void *src, size_t len) {
	char *temp = mx_strnew(len);
	for (unsigned long i = 0; i < len; i++) {
		temp[i] = ((char *)src)[i];
	}
	for (unsigned long i = 0; i < len; i++) {
		((char *)dst)[i] = temp[i];
	}

	free(temp);
	return dst;
}

