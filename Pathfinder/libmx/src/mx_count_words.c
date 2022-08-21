#include "../inc/libmx.h"

int mx_count_words(const char *str, char c) {
    if (str == NULL) {
        return -1;
    }

    bool state = true;
    unsigned counter = 0;
    int i = 0;

    while (str[i]) {
        if (str[i] == c) {
            state = true;
        } else if (state == true) {
            state = false;
            counter++;
        }
        i++;
    }

    return counter;

}
