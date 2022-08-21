#include "../inc/header.h"


void mx_pwd(char *comand)
{
    char **comand_arr = mx_strsplit(comand, ' ');
    int comand_arr_size = mx_get_arr_size(comand_arr);

    if (comand_arr_size > 2)
    {
        mx_printerr("pwd: too many arguments\n");
    }

    if (comand_arr_size == 1)
    {
        printf("%s\n", getenv("PWD"));
    }
    else
    {
        if (comand_arr[1][0] == '-')
        {
            char cwd[1024];
            switch (comand_arr[1][1])
            {
                case 'P':
                    printf("%s\n", getcwd(cwd, sizeof(cwd)));
                    break;
                
                case 'L':
                    printf("%s\n", getenv("PWD"));
                    break;
            
            
                default:
                    mx_printerr("cd: no such file or directory: ");
                    mx_printerr(comand_arr[1]);
                    mx_printerr("\n");
                    break;
            }
        }
    }


    return;
}

