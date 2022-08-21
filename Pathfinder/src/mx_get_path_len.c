#include "../inc/header.h"

int mx_get_path_len(int islands_count, char *paths_array[islands_count * islands_count][islands_count + 3], int line) {
    int len = 0;
    for ( ; paths_array[line][len + 2] != NULL && mx_isalpha(*paths_array[line][len + 2]); len++);
    return len;
}

