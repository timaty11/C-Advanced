#include "../inc/header.h"

dir_data *mx_get_basic_dir_data(char *path, flags *flags) {
    DIR *directory = opendir(path);
    if (directory == NULL) {
        if (errno == 13) {
            char **dir_name = mx_strsplit(path, '/');
            int i = 0;
            for (; dir_name[i + 1] != NULL; i++);

            mx_printerr("uls: ");
            mx_printerr(dir_name[i]);
            mx_printerr(": Permission denied");
            exit(1);
        }
        struct stat info;
        if (lstat(path, &(info)) == -1) {
            mx_printerr("uls: ");
            mx_printerr(path);
            mx_printerr(": No such file or directory\n");
            return NULL;
        } else {
            return mx_node_create(path, path);
        }
    }

    struct dirent *temp = readdir(directory);
    bool created_head = false;
    dir_data *head = NULL;
    
    while (temp != NULL) {
        //// Skip elements which start with '.'
        if (flags->flag_a == 0 && temp->d_name[0] == '.') {
            temp = readdir(directory);
            continue;
        }
        // If it's first iteration we need to create the head of the list
        if (!created_head) {
            head = mx_node_create(temp->d_name, path);

            created_head = true;
            temp = readdir(directory);
            continue;
        }
        mx_add_element(&head, temp->d_name, path);

        flags->flag_p++;
        flags->flag_p--;
        temp = readdir(directory);
    }
    
    closedir(directory);
    return head;
}

