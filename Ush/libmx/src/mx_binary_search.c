#include "../inc/libmx.h"

int mx_binary_search(char **arr, int size, const char *s, int *count) {
    int l = 0, r = size - 1;
    while (l <= r) {
        *count += 1;
        int mid = l + (r - l) / 2;
        if (mx_strcmp(arr[mid], s) == 0) {
            return mid;
        }
        if (mx_strcmp(arr[mid], s) < 0) {
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    *count = 0;
    return -1;
}

