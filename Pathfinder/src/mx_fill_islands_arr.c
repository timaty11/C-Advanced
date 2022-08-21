#include "../inc/libmx.h"

// Check every word in our final array and put it to array of islands

void mx_fill_islands_lines(int file_lines_amount, char *final[file_lines_amount][4], int islands_count, char *islands[islands_count * 2]) {
    bool found_island = false;
    for (int line = 1; line < file_lines_amount; line++) {
        for (int word = 0; word < 2; word++) {
            for (int i = 0; i < islands_count * 2; i++) {
                if (islands[i] != NULL && !mx_strcmp(final[line][word], islands[i])) {
                    found_island = true;
                    break;
                }
            }
            if (!found_island) {
                for (int i = 0; i < islands_count * 2; i++) {
                    if (islands[i] == NULL) {
                        islands[i] = mx_strdup(final[line][word]);
                        break;
                    }
                }
            }
            found_island = false;
        }
    }
}

