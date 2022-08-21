#include "../inc/header.h"

bool mx_check_input_file(int *file_lines_amount, char **file_str_arr) {
    int found_hyphen = 0, found_coma = 0;
    for ( ; file_str_arr[*file_lines_amount] != NULL; *file_lines_amount += 1) {
        if (file_str_arr[*file_lines_amount][0] == '-') {
            mx_printerr("error: line ");
            mx_printerr(mx_itoa(*file_lines_amount + 1));
            mx_printerr(" is not valid\n");
            return 1;
        }
        for (int i = 0; file_str_arr[*file_lines_amount][i] != '\0'; i++) {
            if (file_str_arr[*file_lines_amount][i] == '-') {
                found_hyphen++;
                continue;
            }
            if (file_str_arr[*file_lines_amount][i] == ',') {
                found_coma++;
                if (file_str_arr[*file_lines_amount][i - 1] == '-') {
                    mx_printerr("error: line ");
                    mx_printerr(mx_itoa(*file_lines_amount + 1));
                    mx_printerr(" is not valid\n");
                    return 1;
                }
                continue;
            }
        }
        if (found_coma != 1 || found_hyphen != 1) {
            mx_printerr("error: line ");
            mx_printerr(mx_itoa(*file_lines_amount + 1));
            mx_printerr(" is not valid\n");
            return 1;
        } else {
            found_hyphen = 0;
            found_coma = 0;
        }
    }
    
    return 0;
}

