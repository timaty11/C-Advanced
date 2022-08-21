#ifndef HEADER_H
#define HEADER_H

#include <libmx.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <grp.h>
#include <pwd.h>
#include <sys/types.h>
#include <sys/acl.h>
#include <dirent.h>
#include <sys/errno.h>
#include <sys/xattr.h>
#include <termios.h>
#include <sys/ioctl.h>


typedef struct dir_data {
    char d_name[256];
    char path[256];
    char *chmod;
    struct stat info;
    int files_amount;
    char *user;
    char *group;
    int size;
    int grp;
    int usr;

    struct dir_data *next;
}              dir_data;

typedef struct flags {
    int no_flags;
    int flag_l;
    int flag_a;
    int flag_1; // (the number 1)
    int flag_C;
    int flag_m;
    int flag_p;
}              flags;


flags *mx_set_flags(char * argv, flags *flags);

dir_data *mx_node_create(char *name, char *path);
dir_data *mx_add_element(dir_data **head, char *name, char *path);
dir_data *mx_add_created_node(dir_data **head, dir_data *node);

int mx_get_list_length(dir_data *head);
void mx_list_sort(dir_data *head, int nodes_amount);
void mx_free_list(dir_data *head, flags *flags);

dir_data *mx_get_basic_dir_data(char *path, flags *flags);
dir_data *mx_get_advanced_dir_data(char *path, flags *flags);

// Chmod functions
void mx_get_chmod(dir_data *node);
char check_per(dir_data *node);
char get_Flag_acl(dir_data *node);
char check_chmode_S(char chmod);
char check_chmode_T(char *chmod);


char *check_group(dir_data *total);
char *check_pw(dir_data *total);
char *get_username(dir_data *node);
char *get_groupname(dir_data *node);
void count_size(dir_data *total);


// Output
void mx_output(dir_data *head, flags *flags, int is_dir);
void mx_flag_l_output(dir_data *head);
void mx_signle_line_output(dir_data **head, int terminal_len, bool forced_output);
int mx_count_spaces(dir_data *head, int data_type);
void mx_print_link(dir_data *node);

void print_tab(int len, int maxlen);
void print_names(char **names, int maxlen, int wincol);
void pretty_print(char **names, int row, int num, int maxlen);
int Names_lenght_max(char **names);

#endif
