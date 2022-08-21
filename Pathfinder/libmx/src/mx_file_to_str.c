#include "../inc/libmx.h"

char *mx_file_to_str(const char *file) {
    int p = open(file, O_RDONLY);
    if (p < 0) {
        close(p);
        return NULL;
    }

    int file_size = 0;
    char c;

    while (read(p, &c, 1)) {
        file_size++;
    }
    close(p);

    char *str = mx_strnew(file_size);
    p = open(file, O_RDONLY);
    read(p, str, file_size);
    close(p);
    return str;
}

