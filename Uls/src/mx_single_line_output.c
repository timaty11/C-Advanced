#include "../inc/header.h"


char *mx_get_names_arr(dir_data *head)
{
    dir_data *node = head;
    int names_amount = 0;
    int names_total_len = 0;
    while (node != NULL) {
        names_amount++;
        names_total_len += mx_strlen(node->d_name);
        node = node->next;
    }

    node = head;
    char *names = mx_strnew(names_total_len + names_amount + 50);

    names = mx_strcpy(names, node->d_name);
    names = mx_strcat(names, ",");
    node = node->next;

    for (int i = 1; i < names_amount; i++) {
        names = mx_strcat(names, node->d_name);
        names = mx_strcat(names, ",");
        node = node->next;
    }

    return names;
}


void mx_signle_line_output(dir_data **head, int terminal_len, bool forced_output) {    
    if(isatty(1) && forced_output != 0) {
        char *names = mx_get_names_arr(*head);
        char **names_arr = mx_strsplit(names, ',');

        print_names(names_arr, Names_lenght_max(names_arr), terminal_len);

        names = NULL;
    } else {
        dir_data *node = *head;
        while(node != NULL) {
            mx_printstr(node->d_name);
            if (node->next != NULL) {
                mx_printchar('\n');
            }
            
            node = node->next;
        }
    }
}


void print_tab(int len, int maxlen) {
    int p = maxlen - len;
    int c = p % 8 != 0 ? (p / 8) + 1 : p / 8;
    
    for (int i = 0; i < c; i++) {
        mx_printchar('\t');
    }
}


void print_names(char **names, int maxlen, int wincol) {
    int row;
    int col = (wincol / maxlen) != 0 ? wincol / maxlen : 1;
    int num = 0;

    while(names[num]) { 
        num++;
    }
    if (maxlen * col > wincol && col != 1) {
        col--;
    }
    if (num * maxlen > wincol) {
        row = num / col;
        if (row == 0 || num % col != 0) {
            row++;
        }

        pretty_print(names, row, num, maxlen);
    } else {
        for (int i = 0; names[i]; i++)  {
            mx_printstr(names[i]);
            if (names[i + 1]) {
                print_tab(mx_strlen(names[i]), maxlen);
            }
        }
    }
    mx_printchar('\n');
}


void pretty_print(char **names, int row, int num, int maxlen) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; i + j < num; j += row) {
            mx_printstr(names[i + j]);
            if (names[i + j + 1] && (i + j + row < num)) {
                print_tab(mx_strlen(names[i + j]), maxlen);
            }
        }
        if (i != row - 1) {
            mx_printchar('\n');
        }
    }
}

int Names_lenght_max(char **names) {
    int max = 0;

    for (int i = 0; names[i]; i++) {
        int tmp = mx_strlen(names[i]);
        if (tmp > max) {
            max = tmp;
        }
    }

    max = max % 8 == 0 ? max += 8 : 8 - (max % 8) + max;
    return max;
}

