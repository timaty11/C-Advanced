#include "../inc/libmx.h"

int mx_strcmp(const char *s1, const char *s2) {
	if (s1 == NULL || s2 == NULL) {
		return 1;
	}

    for (int i = 0; (s1[i] != '\0') || (s2[i] != '\0'); i++) {
		if (s1[i] != s2[i])	{
			return s1[i] - s2[i];
		}
	}

	return 0;
}

