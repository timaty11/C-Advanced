#include "../inc/libmx.h"

void mx_printerr(const char *s) {
    int counter = 0;
    while (s[counter]) {
        ++counter;
    }
    write(2, s, counter);
}

