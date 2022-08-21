#include "../inc/header.h"

dir_data *mx_node_create(char *name, char *path) {
    dir_data *node = (dir_data *)malloc(sizeof(dir_data));
    
    for (int i = 0; i < 256; i++) {
        node->d_name[i] = '\0';
    }
    mx_strcpy(node->d_name, name);

    // mx_printstr(name);
    // mx_printstr(" - ");
    // mx_printstr(node->d_name);
    // mx_printchar('\n');

    // int sub_path_len = mx_strlen(path) + mx_strlen(node->d_name) + 8;
    // char sub_path[256];
    // for (int i = 0; i < sub_path_len; i++) {
    //     sub_path[i] = '\0';
    // }
    // sub_path = mx_strcpy(sub_path, path);
    // sub_path = mx_strcat(sub_path, "/");
    // sub_path = mx_strcat(sub_path, node->d_name);

    for (int i = 0; i < 256; i++) {
        node->path[i] = '\0';
    }
    mx_strcpy(node->path, path);
    node->path[mx_strlen(path)] = '/';
    mx_strcat(node->path, node->d_name);

    // node->path = mx_strdup(sub_path);
    node->next = NULL;
    
    // if (sub_path != NULL) {
    //     mx_strdel(&sub_path);
    // }
    return node;
}


dir_data *mx_add_element(dir_data **head, char *name, char *path) {
    dir_data *tmp = *head;
    while (tmp->next) {
        tmp = tmp->next;
    }
    tmp->next = mx_node_create(name, path);

    return tmp->next;
}


dir_data *mx_add_created_node(dir_data **head, dir_data *node) {
    dir_data *tmp = *head;
    while (tmp->next) {
        tmp = tmp->next;
    }
    tmp->next = node;

    return tmp->next;
}


void mx_free_list(dir_data *head, flags *flags) {
    struct dir_data *tmp;

    while (head != NULL) {
        tmp = head;
        head = head->next;
        // if (tmp->d_name != NULL) {
        //     mx_strdel(&tmp->d_name);
        // }
        
        // if (tmp->path != NULL) {
        //     mx_strdel(&tmp->path);
        // }
        
        if (flags->flag_l != 0) {
            mx_strdel(&tmp->chmod);
        }

        tmp->next = NULL;
    }
}


void mx_list_sort(dir_data *head, int nodes_amount) {
    int node_ctr, ctr;
    dir_data *cur_node = head;
    dir_data *next_node = head->next;

    for (node_ctr = nodes_amount - 2; node_ctr >= 0; node_ctr--) {
        cur_node = head;
        next_node = cur_node->next;
        for (ctr = 0; ctr <= node_ctr; ctr++) {
            if (mx_strcmp(cur_node->d_name, next_node->d_name) > 0) {
                char temp_name[256];
                for (int i = 0; i < 256; i++) {
                    temp_name[i] = '\0';
                }

                mx_strcpy(temp_name, cur_node->d_name);
                for (int i = mx_strlen(cur_node->d_name); i < 256; i++) {
                    temp_name[i] = '\0';
                }

                mx_strcpy(cur_node->d_name, next_node->d_name);
                for (int i = mx_strlen(next_node->d_name); i < 256; i++) {
                    cur_node->d_name[i] = '\0';
                }

                mx_strcpy(next_node->d_name, temp_name);
                for (int i = mx_strlen(temp_name); i < 256; i++) {
                    next_node->d_name[i] = '\0';
                }


                char temp_path[256];
                for (int i = 0; i < 256; i++) {
                    temp_path[i] = '\0';
                }

                mx_strcpy(temp_path, cur_node->path);
                for (int i = mx_strlen(cur_node->path); i < 256; i++) {
                    temp_path[i] = '\0';
                }

                mx_strcpy(cur_node->path, next_node->path);
                for (int i = mx_strlen(next_node->path); i < 256; i++) {
                    cur_node->path[i] = '\0';
                }

                mx_strcpy(next_node->path, temp_path);
                for (int i = mx_strlen(temp_path); i < 256; i++) {
                    next_node->path[i] = '\0';
                }
            }

            cur_node = next_node;
            next_node = cur_node->next;
        }
    }
}


int mx_get_list_length(dir_data *head) {
    int counter = 0;
    while (head != NULL) {
        head = head->next;
        counter++;
    }

    return counter;
}

