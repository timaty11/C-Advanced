#include "../inc/libmx.h"

void mx_printint(int n) {
    if (n == 0) {
        mx_printchar('0');
        return;
    }
    int neg = 1;
    if (n < 0) {
        neg = -1;
        mx_printchar('-');
    }

    int temp = n, n_len = 0;
    while (temp != 0) {
        n_len++;
        temp /= 10;
    }

    char n_chars[n_len];
    for (int i = 0; n != 0; i++) {
        n_chars[i] = (char)((n % 10) * neg);
        n /= 10;
    }
    for (int i = n_len - 1; i >= 0; i--) {
        mx_printchar(n_chars[i] + 48);
    }
}

