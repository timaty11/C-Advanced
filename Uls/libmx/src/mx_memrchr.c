#include "../inc/libmx.h"

void *mx_memrchr(const void *s, int c, size_t n) {
	char *temp = (char *)s;

	for (unsigned long i = n - 1; i > 0; i--) {
		if (temp[i] == c) {
			return temp + i;
		}
	}
	if (temp[0] == c) {
		return temp;
	}

	return NULL;
}

