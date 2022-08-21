#include "../inc/header.h"

void mx_save_found_path(int islands_count, int paths_array_size, char *paths_array[paths_array_size][islands_count + 3], char *islands[], int ver[], int d[], int k, int *paths_array_index, int begin_index, int end_point) {
    paths_array[*paths_array_index][0] = mx_strdup(islands[begin_index]);
    paths_array[*paths_array_index][1] = mx_strdup(islands[end_point]);
    paths_array[*paths_array_index][islands_count + 2] = mx_strdup(mx_itoa(d[end_point]));
    
    int h = 2;
    for (int i = k - 1; i >= 0; i--) {
        paths_array[*paths_array_index][h] = mx_strdup(islands[ver[i] - 1]);
        h++;
    }
    *paths_array_index += 1;
}

