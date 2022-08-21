#include "../inc/header.h"


void mx_export(char *comand, env_var_names **head)
{
    char **comand_arr = mx_strsplit(comand, ' ');
    int comand_arr_size = mx_get_arr_size(comand_arr);

    if (comand_arr_size == 1)
    {
        mx_env(comand, *head);
    }
    else
    {
        char **var_to_add = mx_strsplit(comand_arr[1], '=');
        setenv(var_to_add[0], var_to_add[1], 1);

        mx_add_name_element(head, var_to_add[0]);
        mx_del_strarr(&var_to_add);
    }

    mx_del_strarr(&comand_arr);
    return;
}

