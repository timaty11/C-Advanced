#include "../inc/header.h"

void mx_move_paths_arr(int islands_count, char *paths_array[islands_count * islands_count][islands_count + 3], char *islands[], int cur_line, int line_to_put) {
    // Remember the line we need to move
    int line_to_move[islands_count + 3];
    for (int i = 0; i < islands_count + 2; i++) {
        if (paths_array[cur_line][i] != NULL) {
            line_to_move[i] = mx_get_island_index(paths_array[cur_line][i], islands);
        } else {
            line_to_move[i] = -1;
        }
    }
    line_to_move[islands_count + 2] = mx_atoi(paths_array[cur_line][islands_count + 2]);

    // Move previous lines forward until we reach line_to_put
    for (int i = cur_line - 1; i >= line_to_put; i--) {
        if (paths_array[i][0] == NULL) {
            continue;
        }

        // Remember the line we need to move
        int temp[islands_count + 3];
        for (int j = 0; j < islands_count + 2; j++) {
            if (paths_array[i][j] != NULL) {
                temp[j] = mx_get_island_index(paths_array[i][j], islands);
            } else {
                temp[j] = -1;
            }
        }
        
        temp[islands_count + 2] = mx_atoi(paths_array[i][islands_count + 2]);

        for (int j = 0; j < islands_count + 2; j++) {
            if (temp[j] != -1) {
                paths_array[i + 1][j] = mx_strdup(islands[temp[j]]);
            } else {
                paths_array[i + 1][j] = NULL;
            }
        }
        paths_array[i + 1][islands_count + 2] = mx_strdup(mx_itoa(temp[islands_count + 2]));
    }

    // Put in the line_to_put line we saved previously
    for (int j = 0; j < islands_count + 2; j++) {
        if (line_to_move[j] != -1) {
            paths_array[line_to_put][j] = mx_strdup(islands[line_to_move[j]]);
        } else {
            paths_array[line_to_put][j] = NULL;
        }
    }
    paths_array[line_to_put][islands_count + 2] = mx_strdup(mx_itoa(line_to_move[islands_count + 2]));
}

