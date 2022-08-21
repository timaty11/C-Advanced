#include "../inc/libmx.h"

char *mx_del_extra_spaces(const char *str) {
    if (!str) {
        return NULL;
    }
    
    char *temp = mx_strnew(mx_strlen(str));
    int i = 0, j = 0;
    while (str[i]) {
        if (!(mx_isspace(str[i]))) {
            temp[j] = str[i];
            j += 1;
        }
        if (!(mx_isspace(str[i])) && mx_isspace(str[i + 1])) {
            temp[j] = ' ';
            j += 1;
        }
        i += 1;
    }
    char *res = mx_strtrim(temp);
    mx_strdel(&temp);
    
    return res;
}

