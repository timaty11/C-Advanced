#include "../inc/libmx.h"

// Return the amount of elements in NULL terminated array of chars

int mx_get_arr_size(char **arr) {
    int counter = 0;

    while(arr[counter] != NULL) {
        counter++;
    }

    return counter;
}

