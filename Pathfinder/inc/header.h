#ifndef HEADER_H
#define HEADER_H

#include <libmx.h>

// Input check funstions
bool mx_check_input_file(int *file_lines_amount, char **file_str_arr);
bool mx_check_if_file_empty(char *file_str,  char *argv[]);
bool mx_check_final(int file_lines_amount, char *final[file_lines_amount][4], int islands_count, char *islands[islands_count * 2]);
bool mx_check_final_lines(int file_lines_amount, char *final[file_lines_amount][4]);
bool mx_check_final_dups(int file_lines_amount, char *final[file_lines_amount][4]);

void mx_fill_islands_lines(int file_lines_amount, char *final[file_lines_amount][4], int islands_count, char *islands[islands_count * 2]);
void mx_matrix_fill(int file_lines_amount, char *final[file_lines_amount][4], int islands_count, char *islands[islands_count * 2], int matrix[islands_count][islands_count]);

// Main algorythm functions
int mx_get_island_index(char *island_name, char *island_array[]);
void mx_move_paths_arr(int islands_count, char *paths_array[islands_count * islands_count][islands_count + 3], char *islands[], int cur_line, int line_to_put);
void mx_sort_all_pathes(int islands_count, char *paths_array[islands_count * islands_count][islands_count + 3], char *islands[]);


int mx_pathes_initialize(int islands_count, int d[islands_count], int v[islands_count], int begin_index, int matrix[islands_count][islands_count]);
int mx_find_all_pathes(int islands_count, int paths_array_size, char *paths_array[paths_array_size][islands_count + 3], int matrix[islands_count][islands_count], char *islands[], int begin_index, int end_point, int *paths_array_index);
void mx_save_found_path(int islands_count, int paths_array_size, char *paths_array[paths_array_size][islands_count + 3], char *islands[], int ver[], int d[], int k, int *paths_array_index, int begin_index, int end_point);
int mx_check_dup(int islands_count, int paths_array_size, char *paths_array[paths_array_size][islands_count + 3], char *islands[], int line, int begin_index, int end_point);
bool mx_check_path_dup_islands(int i, int index, int *paths_array_index, int islands_count, int paths_array_size, char *paths_array[paths_array_size][islands_count + 3], char *islands[], int begin_index, int end_point);
int mx_get_path_len(int islands_count, char *paths_array[islands_count * islands_count][islands_count + 3], int line);

void mx_print_all_pathes(int islands_count, char *paths_array[islands_count * islands_count][islands_count + 3], int matrix[islands_count][islands_count], char *islands[], int paths_array_size);


#endif

