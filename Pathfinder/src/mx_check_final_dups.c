#include "../inc/header.h"

bool mx_check_final_dups(int file_lines_amount, char *final[file_lines_amount][4]) {
    for (int line_to_check = 1; line_to_check < file_lines_amount; line_to_check++) {
        for (int line = 1; line < file_lines_amount; line++) {
            if (line != line_to_check) {
                if ((!mx_strcmp(final[line_to_check][0], final[line][0]) && !mx_strcmp(final[line_to_check][1], final[line][1])) || 
                    (!mx_strcmp(final[line_to_check][0], final[line][1]) && !mx_strcmp(final[line_to_check][1], final[line][0]))) {
                    mx_printerr("error: duplicate bridges\n");
                    return 1;
                }
            }
        }
    }

    return 0;
}

