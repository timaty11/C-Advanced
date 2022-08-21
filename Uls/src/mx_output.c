#include "../inc/header.h"

void mx_output(dir_data *head, flags *flags, int is_dir)
{
    // Get the size of the window
    struct winsize window_params;
    ioctl(0, TIOCGWINSZ, &window_params);

    // Count the len of output if it was in one line
    int output_len = 0;
    int total_block_size = 0;
    dir_data *node_to_read = head;
    while (node_to_read->next != NULL) {
        output_len += mx_strlen(node_to_read->d_name) + 2;
        total_block_size += node_to_read->info.st_blocks;
        node_to_read = node_to_read->next;
    }
    output_len += mx_strlen(node_to_read->d_name) + 1;
    total_block_size += node_to_read->info.st_blocks;
    

    if (flags->flag_l != 0) {
        if (is_dir == 1) {
            mx_printstr("total ");
            mx_printint(total_block_size);
            mx_printchar('\n');
        }
        
        mx_flag_l_output(head);
    } else {
        mx_signle_line_output(&head, window_params.ws_col, 1);
    }
}


void mx_flag_l_output(dir_data *head) {
    dir_data *node_to_read = head;
    time_t cur_time = time(NULL);
    char *cur_time_string = ctime(&cur_time);
    char cur_year_string[4];
    for (int i = 0; i < 4; i++) {
        cur_year_string[i] = cur_time_string[i + 20];
    }
    int cur_year = mx_atoi(cur_year_string);

    while (node_to_read != NULL) {
        if (node_to_read->chmod != NULL) {
            int count_spaces = mx_count_spaces(head, 0);
            int strlen = mx_strlen(mx_itoa(node_to_read->info.st_nlink));
            mx_printstr(node_to_read->chmod);
            for (int i = 0; i < count_spaces - strlen; i++) {
                mx_printchar(' ');
            }
            mx_printchar(' ');
            mx_printint(node_to_read->info.st_nlink);
            mx_printchar(' ');

            char *name = get_username(node_to_read);
            count_spaces = mx_count_spaces(head, 1);
            strlen = mx_strlen(name);
            mx_printstr(name);
            for (int i = 0; i < count_spaces - strlen; i++) {
                mx_printchar(' ');
            }
            mx_printstr("  ");

            char *group = get_groupname(node_to_read);
            count_spaces = mx_count_spaces(head, 2);
            strlen = mx_strlen(group);
            mx_printstr(group);
            for (int i = 0; i < count_spaces - strlen; i++) {
                mx_printchar(' ');
            }
            mx_printstr("  ");

            count_spaces = mx_count_spaces(head, 3);
            strlen = mx_strlen(mx_itoa(node_to_read->info.st_size)) + 1;
            for (int i = 0; i <= count_spaces - strlen; i++) {
                mx_printchar(' ');
            }
            mx_printint(node_to_read->info.st_size);
            mx_printchar(' ');


            char *file_m_time = ctime(&node_to_read->info.st_mtime);
            char year[4];
            for (int i = 0; i < 4; i++) {
                year[i] = file_m_time[i + 20];
                
            }

            if (mx_atoi(year) != cur_year) {
                for (int i = 4; i <= 10; i++) {
                    mx_printchar(file_m_time[i]);
                }
                for (int i = 19; i < 24; i++) {
                    mx_printchar(file_m_time[i]);
                }
            }
            else {
                for (int i = 4; i < 16; i++) {
                    mx_printchar(file_m_time[i]);
                }
            }
            mx_printchar(' ');
            
            mx_printstr(node_to_read->d_name);
            if (node_to_read->chmod[0] == 'l') {
                mx_print_link(node_to_read);
            }            
            mx_printchar('\n');
        }
        
        node_to_read = node_to_read->next;
    }
}


int mx_count_spaces(dir_data *head, int data_type) {
    struct dir_data *tmp = head;
    int longest_data = 0;
    
    while (tmp != NULL) {
        switch (data_type) {
            case 0:
                if (mx_strlen(mx_itoa(tmp->info.st_nlink)) > longest_data) {
                    longest_data = mx_strlen(mx_itoa(tmp->info.st_nlink));
                }
                break;
            
            case 1:
                if (mx_strlen(get_username(tmp)) > longest_data) {
                    longest_data = mx_strlen(get_username(tmp));
                }
                break;

            case 2:
                if (mx_strlen(get_groupname(tmp)) > longest_data) {
                    longest_data = mx_strlen(get_groupname(tmp));
                }
                break;

            case 3:
                if (mx_strlen(mx_itoa(tmp->info.st_size)) > longest_data) {
                    longest_data = mx_strlen(mx_itoa(tmp->info.st_size));
                }
                break;
            
            default:
                break;
        }

        tmp = tmp->next;
    }
    
    return longest_data;
}


void mx_print_link(dir_data *node) {
    ssize_t buf_size = node->info.st_size == 0 ? 100 : node->info.st_size + 1;
    char *buf = mx_strnew(buf_size);
    ssize_t nbytes = readlink(node->path, buf, buf_size);

    mx_printstr(" -> ");
    if (nbytes >= 0) {
        mx_printstr(buf);
    }
    mx_strdel(&buf);
}

