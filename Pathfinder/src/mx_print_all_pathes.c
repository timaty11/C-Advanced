#include "../inc/header.h"
    
void mx_print_all_pathes(int islands_count, char *paths_array[islands_count * islands_count][islands_count + 3], int matrix[islands_count][islands_count], char *islands[], int paths_array_size) {
    for (int i = 0; i < paths_array_size; i++) {
        if (paths_array[i][0] != NULL) {
            mx_printstr("========================================\n");

            mx_printstr("Path: ");
            mx_printstr(paths_array[i][0]);
            mx_printstr(" -> ");
            mx_printstr(paths_array[i][1]);
            mx_printchar('\n');
            mx_printstr("Route: ");

            for (int j = 2; paths_array[i][j] != NULL && j < islands_count + 2; j++) {
                mx_printstr(paths_array[i][j]);
                // If there is next element in the route we must print the ' -> ' in console
                if (paths_array[i][j + 1] != NULL && mx_isalpha(*paths_array[i][j + 1])) {
                    mx_printstr(" -> ");
                }
            }

            mx_printchar('\n');
            mx_printstr("Distance: ");

            // If there is more than two elements in our Route (4th element is not empty) we need to print distance like this:
            // (island1 -> island2) + (island2 -> island3) + (...) = total_dist
            if (paths_array[i][4] != NULL) {
                for (int j = 2; paths_array[i][j + 1] != NULL && mx_isalpha(*paths_array[i][j + 1]); j++) {
                    mx_printint(matrix[mx_get_island_index(paths_array[i][j], islands)][mx_get_island_index(paths_array[i][j + 1], islands)]);
                    if (paths_array[i][j + 2] != NULL && mx_isalpha(*paths_array[i][j + 2])) {
                        mx_printstr(" + ");
                    }
                }

                mx_printstr(" = ");
                mx_printstr(paths_array[i][islands_count + 2]);
            } else {
                mx_printstr(paths_array[i][islands_count + 2]);
            }
            mx_printstr("\n========================================\n");
        }
        else {
            break;
        }
    }

    return;
}

