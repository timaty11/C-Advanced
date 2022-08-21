#include "../inc/header.h"

void mx_matrix_fill(int file_lines_amount, char *final[file_lines_amount][4], int islands_count, char *islands[islands_count * 2], int matrix[islands_count][islands_count]) {
    for (int island_index = 0; island_index < islands_count; island_index++) {
        // Check our file (final array) for island name we are looking at
        for (int line = 1; line < file_lines_amount; line++) {
            for (int word = 0; word < 2; word++) {
                if (!mx_strcmp(final[line][word], islands[island_index])) {
                    if (word == 0) {
                        matrix[island_index][mx_get_island_index(final[line][word + 1], islands)] = mx_atoi(final[line][2]);
                        matrix[island_index][mx_get_island_index(final[line][word + 1], islands)] = mx_atoi(final[line][2]);
                    } else if (word == 1) {
                        matrix[island_index][mx_get_island_index(final[line][word - 1], islands)] = mx_atoi(final[line][2]);
                        matrix[island_index][mx_get_island_index(final[line][word - 1], islands)] = mx_atoi(final[line][2]);
                    }
                }
            }
        }
    }
}

