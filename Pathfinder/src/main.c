#include "../inc/header.h"

int main(int argc, char *argv[]) {
    // Check amount of arguments
    if (argc != 2) {
        mx_printerr("usage: ./pathfinder [filename]\n");
        return 1;
    }

    // Try read from the file
    char *file_str = mx_file_to_str(argv[1]);
    if (mx_check_if_file_empty(file_str, argv)) {
        return 1;
    } 

    // Split readen string to array of strings using '\n' as delim
    char **file_str_arr = mx_strsplit(file_str, '\n');

    // First line must be matrix positive digit. If not - error
    for (int i = 0; file_str_arr[0][i] != '\0'; i++) {
        if (!mx_isdigit(file_str_arr[0][i])) {
            mx_printerr("error: line 1 is not valid\n");
            return 1;
        }
    }

    // Islands array - array of islands names
    int islands_count = mx_atoi(file_str_arr[0]);
    char *islands[islands_count * 2];
    for (int i = 0; i < islands_count * 2; i++) {
        islands[i] = NULL;
    }

    // Create matrix for our islands roads and fill it with zero
    int matrix[islands_count][islands_count];
    for (int i = 0; i < islands_count; i++) {
        for (int j = 0; j < islands_count; j++) {
            matrix[i][j] = 0;
        }
    }

    // Array of found Pathes. Has this struct:
    // begin_island, end_island, island1 .. islandN, distance
    // island1 .. islandN has the size of islands_count
    int paths_array_size = islands_count * islands_count;
    char *paths_array[paths_array_size][islands_count + 3];
    for (int i = 0; i < paths_array_size; i++) {
        for (int j = 0; j < islands_count + 3; j++) {
            paths_array[i][j] = NULL;
        }
    }

    // Check for the invalid input in the file:
    // Name of the islands can't be empty, they must be separated by - and the number in the end
    // must be separated by , If there is the amount of , and - is not 1 for each then print the error
    int file_lines_amount = 1;
    if (mx_check_input_file(&file_lines_amount, file_str_arr) != 0) {
        return 1;
    }

    // Separate lines of the file to 3 strings and put it into array so the final will look like this:
    // final[line][word][letter]
    char *final[file_lines_amount][4];
    for (int i = 0; file_str_arr[i] != NULL; i++) {
        char **temp1 = mx_strsplit(file_str_arr[i], '-');
        char **temp2 = mx_strsplit(temp1[1], ',');
        if (i != 0 && (temp1[1] == NULL || temp2[1] == NULL)) {
            mx_printerr("error: line ");
            mx_printerr(mx_itoa(i + 1));
            mx_printerr(" is not valid\n");
            return 1;
        }
        if (i != 0 && !mx_strcmp(temp1[0], temp2[0])) {
            mx_printerr("error: line ");
            mx_printerr(mx_itoa(i + 1));
            mx_printerr(" is not valid\n");
            return 1;
        }
        final[i][0] = mx_strdup(temp1[0]);
        
        if (i != 0) {
            final[i][1] = mx_strdup(temp2[0]);
            final[i][2] = mx_strdup(temp2[1]);
            final[i][3] = NULL;
        }
    }
    
    // Checking if final array is valid and filling islands array with it
    if (mx_check_final(file_lines_amount, final, islands_count, islands)) {
        return 1;
    }
    
    // Check if the amount of islands in first line is the same to the actual amount of islands given in the file
    int check_island_amount = 0;
    for ( ; islands[check_island_amount] != NULL; check_island_amount++);
    if (check_island_amount != islands_count) {
        mx_printerr("error: invalid number of islands\n");
        return 1;
    }

    // Check out every island name is islands array
    mx_matrix_fill(file_lines_amount, final, islands_count, islands, matrix);

    // Go through all the islands and find shortest path for all of them
    int paths_array_index = 0;
    for (int begin_index = 0; begin_index < islands_count; begin_index++) {
        for (int end_point = 0; end_point < islands_count; end_point++) {
            // Skip the case when end point and starts point are the same
            if (end_point == begin_index) {
                continue;
            }
            
            if (mx_find_all_pathes(islands_count, paths_array_size, paths_array, matrix, islands, begin_index, end_point, &paths_array_index) != 0) {
                return 1;
            }
        }
    }

    // mx_move_paths_arr(islands_count, paths_array, islands, 11, 2);
    mx_sort_all_pathes(islands_count, paths_array, islands);
    mx_sort_all_pathes(islands_count, paths_array, islands);

    mx_print_all_pathes(islands_count, paths_array, matrix, islands, paths_array_size);
    
    return 0;
}

