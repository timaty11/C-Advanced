#include "../inc/libmx.h"

void *mx_memchr(const void *s, int c, size_t n) {
	char *temp = (char *)s;

	for (unsigned long i = 0; *temp != 0 && i < n; temp++ && i++) {
		if (*temp == c) {
			return temp;
		}
	}

	return NULL;
}

