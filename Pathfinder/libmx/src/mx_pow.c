#include "../inc/libmx.h"

double mx_pow(double n, unsigned int pow) {
    if (n == 0) {
        return 0;
    } else if (pow == 0) {
        return 1;
    } else {
        double res = 1;
        for (unsigned int i = 0; i < pow; i++) {
            res *= n;
        }
        return res;
    }
}

