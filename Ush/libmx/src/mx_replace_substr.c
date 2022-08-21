#include "../inc/libmx.h"

char *mx_replace_substr(const char *str, const char *sub, const char *replace) {
	if (str == NULL || sub == NULL || replace == NULL) {
		return NULL;
	}

	int str_len = mx_strlen(str), sub_len = mx_strlen(sub), rep_len = mx_strlen(replace);
	int i = 0, j = 0;
	int count = mx_count_substr(str, sub);
	char *newstr = mx_strnew(str_len - (count * sub_len) + (count * rep_len));

	for (; *str != '\0'; str++) {
		if (*str == *sub) {
			if (mx_strncmp(str, sub, sub_len) == 0) {
				j = 0;
				while (replace[j] != '\0') {
					newstr[i] = replace[j];
					j++;
					i++;
				}
				str = str + sub_len - 1;
			} else {
				newstr[i] = *str;
				i++;
			}
		} else {
			newstr[i] = *str;
			i++;
		}
	}

	return newstr;
}
