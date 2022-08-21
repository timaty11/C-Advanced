#include "../inc/libmx.h"

bool mx_check_final_lines(int file_lines_amount, char *final[file_lines_amount][4]) {
    for (int line = 1; line < file_lines_amount; line++) {
        for (int word = 0; final[line][word] != NULL; word++) {
            for (int letter = 0; final[line][word][letter] != '\0'; letter++) {
                if (word < 2) {
                    if (!mx_isalpha(final[line][word][letter])) {
                        mx_printerr("error: line ");
                        mx_printerr(mx_itoa(line + 1));
                        mx_printerr(" is not valid\n");
                        return 1;
                    }
                } else {
                    if (!mx_isdigit(final[line][word][letter])) {
                        mx_printerr("error: line ");
                        mx_printerr(mx_itoa(line + 1));
                        mx_printerr(" is not valid\n");
                        return 1;
                    }
                }
            }
        }
    }

    return 0;
}

