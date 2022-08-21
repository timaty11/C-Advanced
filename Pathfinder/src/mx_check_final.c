#include "../inc/header.h"

// Checking if final array is valid and filling islands array with it

bool mx_check_final(int file_lines_amount, char *final[file_lines_amount][4], int islands_count, char *islands[islands_count * 2]) {
    // Elements must be like this: [first_place], [second_place], [distance]
    // Places must contain only chars, distance must be only positive integer
    // If not - print error
    if (mx_check_final_lines(file_lines_amount, final)) {
        return 1;
    }

    // Check for duplicates in final array
    if (mx_check_final_dups(file_lines_amount, final)) {
        return 1;
    }

    // Check every word in our final array and put it to array of islands
    mx_fill_islands_lines(file_lines_amount, final, islands_count, islands);

    return 0;
}

