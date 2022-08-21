#include "../inc/header.h"


void mx_unset(char *comand)
{
    char **comand_arr = mx_strsplit(comand, ' ');
    int comand_arr_size = mx_get_arr_size(comand_arr);

    if (comand_arr_size < 2)
    {
        printf("u$h> unset: not enough arguments\n");
        return;
    }
    else
    {
        for (int i = 1; i < comand_arr_size; i++)
        {
            for (int j = 0; j < mx_strlen(comand_arr[i]); j++)
            {
                if (comand_arr[i][j] == '.')
                {
                    printf("u$h> unset: %s: invalid parameter name\n", comand_arr[i]);
                    return;
                }
            }
            
            if (unsetenv(comand_arr[i]) == -1)
            {
                printf("u$h> unset: %s: invalid parameter name\n", comand_arr[i]);
                return;
            }
        }
    }
}

