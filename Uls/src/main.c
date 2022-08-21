#include "../inc/header.h"


int main(int argc, char * argv[]) {
    char *dirs_to_check[argc];
    char * files_to_print[argc];
    int dirs_to_check_amount = 0, files_to_print_amount = 0, flags_amount = 0;
    for (int i = 0; i < argc; i++) {
        dirs_to_check[i] = NULL;
        files_to_print[i] = NULL;
    }

    dir_data *head = NULL;
    flags *flags = malloc(sizeof(flags));
    flags->flag_l = 0;
    flags->flag_a = 0;
    flags->flag_1 = 0; // (the number 1)
    flags->flag_C = 0;
    flags->flag_m = 0;
    flags->flag_p = 0;
    flags->no_flags = 1;

    bool flags_only = true;
    
    if (argc == 1) {
        head = mx_get_basic_dir_data(".", flags);

        mx_list_sort(head, mx_get_list_length(head));
        mx_output(head, flags, 0);
        if (!isatty(1)) {
            mx_printchar('\n');
        }

        flags_only = false;
        mx_free_list(head, flags);
    } else {
        for (int i = 1; i < argc; i++) {
            if (argv[i][0] == '-') {
                flags = mx_set_flags(argv[i], flags);
                flags_amount++;
            } else {
                for (int j = i; j < argc; j++) {
                    DIR *directory = opendir(argv[j]);
                    if (directory == NULL) {
                        struct stat info;
                        if (lstat(argv[j], &(info)) == -1) {
                            mx_printerr("uls: ");
                            mx_printerr(argv[j]);
                            mx_printerr(": No such file or directory\n");
                            continue;
                        } else {
                            flags_only = false;
                            files_to_print[files_to_print_amount] = mx_strdup(argv[j]);
                            files_to_print_amount++;
                            continue;
                        }
                    }
                    flags_only = false;
                    dirs_to_check[dirs_to_check_amount] = mx_strdup(argv[j]);
                    dirs_to_check_amount++;
                    
                    if (directory != NULL) {
                        closedir(directory);
                    }
                }
                
                break;
            }
        }

        // Sort the names of directories
        if (files_to_print_amount != 0) {
            mx_bubble_sort(files_to_print, files_to_print_amount);
        }
        if (dirs_to_check_amount != 0) {
            mx_bubble_sort(dirs_to_check, dirs_to_check_amount);
        }
    }

    if (files_to_print_amount == 0 && dirs_to_check_amount == 0 && argc - flags_amount > 1) {
        exit(1);
    }

    if (flags->no_flags == 0 && files_to_print_amount == 0 && dirs_to_check_amount == 0) {
        head = mx_get_advanced_dir_data(".", flags);
        mx_list_sort(head, mx_get_list_length(head));
        mx_output(head, flags, 1);
    } else {
        if (files_to_print_amount != 0) {
            bool created_head = false;
            for (int i = 0; i < files_to_print_amount; i++) {
                if (flags->no_flags != 0) {
                    if (!created_head) {
                        head = mx_get_basic_dir_data(files_to_print[i], flags);
                        created_head = true;
                    } else {
                        mx_add_element(&head, files_to_print[i], files_to_print[i]);
                    }
                } else if (flags->flag_l != 0) {
                    if (!created_head) {
                        head = mx_get_advanced_dir_data(files_to_print[i], flags);
                        created_head = true;
                    } else {
                        dir_data *node = mx_get_advanced_dir_data(files_to_print[i], flags);
                        mx_add_created_node(&head, node);
                    }
                } else if (flags->flag_1 != 0) {
                    if (!created_head) {
                        head = mx_get_basic_dir_data(files_to_print[i], flags);
                        created_head = true;
                    } else {
                        mx_add_element(&head, files_to_print[i], files_to_print[i]);
                    }
                    
                    mx_list_sort(head, mx_get_list_length(head));
                    mx_signle_line_output(&head, 0, 1);
                    mx_printchar('\n');
                }
            }

            // Print name of checked directory
            mx_output(head, flags, 0);
            if (dirs_to_check_amount != 0) {
                mx_printchar('\n');
            }

            mx_free_list(head->next, flags);
            head->next = NULL;
        }

        if (flags->no_flags != 0 && !isatty(1) && files_to_print_amount != 0) {
            mx_printchar('\n');
        }

        bool prev_was_null = false;
        for (int i = 0; i < dirs_to_check_amount; i++) {
            if (flags->no_flags != 0) {
                head = mx_get_basic_dir_data(dirs_to_check[i], flags);

                if (dirs_to_check_amount == 1 && head == NULL) {
                    continue;
                }

                // In case if there is nothing inside the directory print just its name
                if (head == NULL) {
                    if (!prev_was_null && i != 0) {
                        mx_printchar('\n');
                    }
                    mx_printstr(dirs_to_check[i]);
                    mx_printstr(":\n");
                    if (i + 1 != dirs_to_check_amount) {
                        mx_printchar('\n');
                    }

                    prev_was_null = true;
                    continue;
                }
            } else if (flags->flag_C != 0) {
                mx_printint(flags->flag_C);
                head = mx_get_basic_dir_data(dirs_to_check[i], flags);
                
                // In case if there is nothing inside the directory print just its name
                if (head == NULL) {
                    mx_printstr(dirs_to_check[i]);
                    mx_printstr(":\n\n");
                    continue;
                }

                mx_list_sort(head, mx_get_list_length(head));
                mx_output(head, flags, 1);
                mx_printchar('\n');
            } else if (flags->flag_l != 0) {
                head = mx_get_advanced_dir_data(dirs_to_check[i], flags);
                
                // In case if there is nothing inside the directory print just its name
                if (dirs_to_check_amount == 1 && head == NULL) {
                    continue;
                }
                if (head == NULL) {
                    if (!prev_was_null && i != 0) {
                        mx_printchar('\n');
                    }
                    mx_printstr(dirs_to_check[i]);
                    mx_printstr(":\n");
                    if (i + 1 != dirs_to_check_amount) {
                        mx_printchar('\n');
                    }

                    prev_was_null = true;
                    continue;
                }
            } else if (flags->flag_1 != 0) {
                head = mx_get_basic_dir_data(dirs_to_check[i], flags);

                // In case if there is nothing inside the directory print just its name
                if (head == NULL) {
                    mx_printstr(dirs_to_check[i]);
                    mx_printstr(":\n\n");
                    continue;
                }
                
                mx_list_sort(head, mx_get_list_length(head));
                mx_signle_line_output(&head, 0, 1);
                mx_printchar('\n');
            } else if (flags->flag_a != 0 && flags->flag_l == 0) {
                head = mx_get_basic_dir_data(dirs_to_check[i], flags);

                if (dirs_to_check_amount == 1 && head == NULL) {
                    continue;
                }

                // In case if there is nothing inside the directory print just its name
                if (head == NULL) {
                    mx_printstr(dirs_to_check[i]);
                    mx_printstr(":\n");
                    if (i + 1 != dirs_to_check_amount) {
                        mx_printchar('\n');
                    }

                    continue;
                }
                
            }

            mx_list_sort(head, mx_get_list_length(head));

            // Print name of checked directory
            if (!isatty(1) && i != 0 && !prev_was_null) {
                mx_printchar('\n');
            }
            
            if (isatty(1) && i != 0) {
                mx_printchar('\n');
            }

            if (dirs_to_check_amount > 1) {
                mx_printstr(dirs_to_check[i]);
                mx_printstr(":\n");
            }
            
            mx_output(head, flags, 1);
            prev_was_null = false;

            if(!isatty(1) && flags->no_flags != 0) {
                mx_printchar('\n');
            }
            
            mx_free_list(head->next, flags);
            head->next = NULL;
        }
    }

    if (flags != NULL) {
        free(flags);
    }

    return 0;
}

