#include "../inc/header.h"

int mx_check_dup(int islands_count, int paths_array_size, char *paths_array[paths_array_size][islands_count + 3], char *islands[], int line, int begin_index, int end_point) {
    if (paths_array[line][0] != NULL) {
        if ((!mx_strcmp(paths_array[line][0], islands[begin_index]) && !mx_strcmp(paths_array[line][1], islands[end_point]))) {
            return 1;
        } else if ((!mx_strcmp(paths_array[line][1], islands[begin_index]) && !mx_strcmp(paths_array[line][0], islands[end_point]))) {
            return 2;
        }
    }
    return 0;
}

