#include "../inc/header.h"

bool mx_check_path_dup_islands(int i, int index, int *paths_array_index, int islands_count, int paths_array_size, char *paths_array[paths_array_size][islands_count + 3], char *islands[], int begin_index, int end_point) {
    for (int z = 1; z <= *paths_array_index; z++) {
        if (mx_check_dup(islands_count, paths_array_size, paths_array, islands, *paths_array_index - z, begin_index, end_point) != 0) {
            if (*paths_array_index - z >= 0) {
                if (paths_array[*paths_array_index - z][0] != NULL) {
                    if (!mx_strcmp(islands[i], paths_array[*paths_array_index - z][index + 3])) {
                        return 1;
                    }
                }
            }
        }
    }

    return 0;
}

