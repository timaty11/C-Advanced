#include "../inc/libmx.h"

int mx_sqrt(int x) {
    if (x <= 0) {
        return 0;
    }

    int result = 0;
    int i = 1;

    while (1) {
        result = i * i;
        if (result == x) {
            return i;
        }
        else if (result > x) {
            return 0;
        }
        else {
            i++;
        }
    }
}

