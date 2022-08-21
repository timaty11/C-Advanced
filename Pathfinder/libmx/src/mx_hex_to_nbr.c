#include "../inc/libmx.h"

unsigned long mx_hex_to_nbr(const char *hex) {
    if (!hex) {
        return 0;
    }
    int i = 0;
    for (i = 0; hex[i] != '\0'; i++);

    unsigned long result = 0, dec = 1;

    for (int j = i - 1; j >= 0; j--) {
        if (hex[j] >= 48 && hex[j] <= 57) {
            result += ((hex[j] - 48) * dec);
            dec *= 16;
        } else if ((hex[j] >= 65 && hex[j] <= 90) || (hex[j] >= 97 && hex[j] <= 122)) {
            if (hex[j] >= 65 && hex[j] <= 90) {
                result += ((hex[j] - 55) * dec);
                dec *= 16;
            } else {
                result += ((hex[j] - 87) * dec);
                dec *= 16;
            }
        }
    }
    return result;
}

