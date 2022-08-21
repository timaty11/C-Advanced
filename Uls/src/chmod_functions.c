#include "../inc/header.h"

char check_per(dir_data *node) {
    if ((((node->info.st_mode) & S_IFMT) == S_IFDIR)) {
        return 'd';
    } else if ((((node->info.st_mode) & S_IFMT) == S_IFLNK)) {
        return 'l';
    } else if ((((node->info.st_mode) & S_IFMT) == S_IFBLK)) {
        return 'b';
    } else if ((((node->info.st_mode) & S_IFMT) == S_IFCHR)) {
        return 'c';
    } else if ((((node->info.st_mode) & S_IFMT) == S_IFIFO)) {
        return 'p';
    } else if ((((node->info.st_mode) & S_IFMT) == S_IFSOCK)) {
        return 's';
    } else if ((((node->info.st_mode) & S_IFMT) == S_IFWHT)) {
        return 'w';
    }

    return '-';
}

char get_Flag_acl(dir_data *node) {
    acl_t tmp = acl_get_file(node->path, ACL_TYPE_EXTENDED);
    
    if (tmp) {
        acl_free(tmp);
        return '+';
    }
    if (listxattr(node->path, NULL, 0, XATTR_NOFOLLOW) > 0) {
        return '@';
    }
    return ' ';
}

char check_chmode_S(char chmod) {
    return chmod == '-' ? 'S' : 's';
}

char check_chmode_T(char *chmod) {
    return chmod[9] == '-' ? 'T' : 't';
}

