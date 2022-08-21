#include "../inc/libmx.h"

char *mx_nbr_to_hex(unsigned long nbr) {
    if (nbr > 4294967295){
        return 0;
    }
    unsigned int tmp = nbr;
    int r, size = 0, j = 0;


    while (nbr != 0) {
        size++;
        nbr /= 16;
    }

    char *hex = (char *)malloc(size);
    while (tmp != 0) {
        r = tmp % 16;

        if (r < 10) {
            hex[j] = 48 + r;
        } else {
            hex[j] = 87 + r;
        }
        j++;
        tmp /= 16;
    }
    j--;
    for (int i = 0; i < j; i++, j--) {
        char nbr = hex[i];
        hex[i] = hex[j];
        hex[j] = nbr;
    }

    return hex;
}

