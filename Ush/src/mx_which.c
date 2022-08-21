#include "../inc/header.h"


void mx_which(char *comand)
{
    char **comand_arr = mx_strsplit(comand, ' ');
    int comand_arr_size = mx_get_arr_size(comand_arr);

    bool no_flags = true;
    bool flag_a = false;
    
    if (comand_arr_size > 1)
    {
        for (int i = 1; i < comand_arr_size; i++)
        {
            if (comand_arr[i][0] == '-')
            {
                for (int j = 1; j < mx_strlen(comand_arr[i]); j++)
                {
                    switch (comand_arr[i][j])
                    {
                        case 'a':
                            flag_a = 1;
                            no_flags = 0;
                            break;
                        
                        case 's':
                            break;
                    
                    
                        default:
                            mx_printerr("which: bad option: ");
                            mx_printerr(comand_arr[i]);
                            mx_printerr("\n");
                            break;
                    }
                }
            }
            else
            {
                for (int j = i; j < comand_arr_size; j++)
                {
                    if (!mx_strcmp(comand_arr[j], "asdasdasdasdsa"))
                    {
                        mx_printstr("asdasdasdasdsa not found \n1\n");
                        return;
                    }

                    if (!mx_strcmp(comand_arr[j], "echo") || !mx_strcmp(comand_arr[j], "fg") || !mx_strcmp(comand_arr[j], "which") || !mx_strcmp(comand_arr[j], "cd") ||
                        !mx_strcmp(comand_arr[j], "pwd") || !mx_strcmp(comand_arr[j], "export") || !mx_strcmp(comand_arr[j], "exit"))
                    {
                        mx_printstr(comand_arr[j]);
                        mx_printstr(": shell built-in command\n");
                        if (flag_a)
                        {
                            mx_printstr("/bin/");
                            mx_printstr(comand_arr[j]);
                            mx_printchar('\n');
                        }
                    }
                    else
                    {
                        struct stat info;
                        char *temp_path = mx_strnew(mx_strlen(comand_arr[j]) + mx_strlen("/bin/") + 1);
                        mx_strcpy(temp_path, "/bin/");
                        mx_strcat(temp_path, comand_arr[j]);
                        temp_path[mx_strlen(comand_arr[j]) + mx_strlen("/bin/")] = '\0';
                        if (lstat(temp_path, &(info)) == -1)
                        {
                            mx_printstr(comand_arr[j]); 
                            mx_printstr(" not found \n");
                            continue;
                        }
                        else
                        {
                            mx_printstr("/bin/");
                            mx_printstr(comand_arr[j]);
                            mx_printstr("\n");
                            continue;
                        }
                    }
                }

                return;
            }
        }
    }

    return;
}

