#include "../inc/header.h"

dir_data *mx_get_advanced_dir_data(char *path, flags *flags) {
    DIR *directory = opendir(path);
    if (directory == NULL) {
        if (errno == 13) {
            char **dir_name = mx_strsplit(path, '/');
            int i = 0;
            for (; dir_name[i + 1] != NULL; i++);

            mx_printerr("uls: ");
            mx_printerr(dir_name[i]);
            mx_printerr(": Permission denied\n");
            exit(1);
        }
        struct stat info;
        if (lstat(path, &(info)) == -1) {
            mx_printerr("uls: ");
            mx_printerr(path);
            mx_printerr(": No such file or directory\n");
            return NULL;
        } else {
            dir_data *node = mx_node_create(path, path);

            count_size(node);
            
            lstat(path, &(node->info));
            mx_get_chmod(node);
            node->files_amount = 1;

            return node;
        }
    }

    struct dirent *temp = readdir(directory);
    dir_data *head = NULL;
    bool created_head = false;
    int list_length = 0;
    
    while (temp != NULL) {
        // Skip elements which start with '.'
        if (flags->flag_a == 0 && temp->d_name[0] == '.') {
            temp = readdir(directory);
            continue;
        }

        // If it's first iteration we need to create the head of the list
        if (!created_head) {
            head = mx_node_create(temp->d_name, path);
            created_head = true;
            list_length++;
            temp = readdir(directory);
            continue;
        } else {
            mx_add_element(&head, temp->d_name, path);
            list_length++;
        }

        temp = readdir(directory);
    }

    // mx_printstr("\n=========BEFORE SORT=========\n");
    // dir_data *temmmmp = head;
    // while (temmmmp != NULL) {
    //     mx_printstr(temmmmp->d_name);
    //     mx_printchar('\n');

    //     temmmmp = temmmmp->next;
    // }

    if (head != NULL) {
        mx_list_sort(head, list_length);
    }

    // mx_printstr("\n=========AFTER SORT=========\n");
    // temmmmp = head;
    // while (temmmmp != NULL) {
    //     mx_printstr(temmmmp->d_name);
    //     mx_printchar('\n');

    //     temmmmp = temmmmp->next;
    // }
    // mx_printstr("\n==================\n");

    dir_data *node = head;
    while(node != NULL) {
        if (lstat(node->path, &(node->info)) == -1) {
            perror("lstat");
            exit(EXIT_FAILURE);
        }

        count_size(node);
        mx_get_chmod(node);

        node = node->next;
    }
    
    closedir(directory);
    return head;
}


void mx_get_chmod(dir_data *node) {
    node->chmod = (char *)malloc(sizeof(char) * 12);
    
    node->chmod[0] = check_per(node);
    node->chmod[1] = (S_IRUSR & node->info.st_mode) ? 'r' : '-';
    node->chmod[2] = (S_IWUSR & node->info.st_mode) ? 'w' : '-';
    node->chmod[3] = (S_IXUSR & node->info.st_mode) ? 'x' : '-';
    node->chmod[4] = (S_IRGRP & node->info.st_mode) ? 'r' : '-';
    node->chmod[5] = (S_IWGRP & node->info.st_mode) ? 'w' : '-';
    node->chmod[6] = (S_IXGRP & node->info.st_mode) ? 'x' : '-';
    node->chmod[7] = (S_IROTH & node->info.st_mode) ? 'r' : '-';
    node->chmod[8] = (S_IWOTH & node->info.st_mode) ? 'w' : '-';
    node->chmod[9] = (S_IXOTH & node->info.st_mode) ? 'x' : '-';
    node->chmod[10] = get_Flag_acl(node);
    node->chmod[11] = '\0';
    S_ISUID & node->info.st_mode ? node->chmod[3] = check_chmode_S(node->chmod[3]) : 0;
    S_ISGID & node->info.st_mode ? node->chmod[6] = check_chmode_S(node->chmod[6]) : 0;
    S_ISVTX & node->info.st_mode ? node->chmod[9] = check_chmode_T(node->chmod) : 0;
}


void count_size(dir_data *total) {
    char *name_grp = check_group(total);
    char *name_pw = check_pw(total);
    if (total->size < total->info.st_size) {
        total->size = total->info.st_size;
    }

    if (total->grp < mx_strlen(name_grp)) {
        total->grp = mx_strlen(name_grp);
    }

    if (total->usr < mx_strlen(name_pw)) {
        total->usr = mx_strlen(name_pw);
    }
}

char *get_username(dir_data *node) {
    struct passwd *pw = getpwuid(node->info.st_uid);
    char *name = pw ? mx_strdup(pw->pw_name) : mx_itoa(node->info.st_uid);
    
    return name;
}

char *get_groupname(dir_data *node) {
    struct group *grp = getgrgid(node->info.st_gid);
    char *name = grp ? mx_strdup(grp->gr_name) : mx_itoa(node->info.st_gid);
    
    return name;
}

char *check_group(dir_data *total) {
    struct group *grp = getgrgid(total->info.st_gid);
    return grp ? mx_strdup(grp->gr_name) : mx_itoa(total->info.st_gid);
}

char *check_pw(dir_data *total) {
    struct passwd *pw = getpwuid(total->info.st_uid);
    return pw ? mx_strdup(pw->pw_name) : mx_itoa(total->info.st_uid);
}

