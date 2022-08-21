#include "../inc/header.h"

bool mx_check_if_file_empty(char *file_str,  char *argv[]) {
    if (file_str == NULL) {
        mx_printerr("error: file ");
        mx_printerr(argv[1]);
        mx_printerr(" does not exist\n");
        return 1;
    }
    
    if (file_str[0] == 0) {
        mx_printerr("error: file ");
        mx_printerr(argv[1]);
        mx_printerr(" is empty\n");
        return 1;
    }

    return 0;
}

