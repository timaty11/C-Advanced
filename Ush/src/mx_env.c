#include "../inc/header.h"


void mx_env(char *comand, env_var_names *List_var_names_head)
{
    char **comand_arr = mx_strsplit(comand, ' ');
    int comand_arr_size = mx_get_arr_size(comand_arr);
    
    env_var_names *tmp = List_var_names_head->next;

    if (comand_arr_size == 1)
    {
        while (tmp != NULL)
        {
            printf("%s=%s\n", tmp->var_name, getenv(tmp->var_name));
            tmp = tmp->next;
        }
    }
    else if (comand_arr[1][0] == '-')
    {
        char *temp = mx_strdup(&comand_arr[1][1]);
        switch (comand_arr[1][1])
        {
            case 'u':
                if (comand_arr_size <= 2)
                {
                    printf("env: option requires an argument -- u\n");
                    printf("usage: env [-iv] [-P utilpath] [-S string] [-u name]\n");
                    printf("\t\tenv: option requires an argument -- u\n");
                    return;
                }
                else if (sortanul(&List_var_names_head, comand_arr[2]) == 1)
                {
                    unsetenv(comand_arr[2]);
                    mx_del_name_node(&List_var_names_head, comand_arr[2]);
                }
                else
                {
                    printf("Set the environmental variable %s\n", comand_arr[2]);
                    return;
                }
                break;

            case 'P':
                while (tmp != NULL)
                {
                    printf("%s\n", getenv(tmp->var_name));
                    tmp = tmp->next;
                }
                break;

            case 'i':
                for (int i = 2; comand_arr[i] != NULL; i++)
                {
                    bool found_ravno = false;
                    for (int j = 0; j < mx_strlen(comand_arr[i]); j++)
                    {
                        if (comand_arr[i][j] == '=')
                        {
                            found_ravno = true;
                            break;
                        }
                    }
                    if (found_ravno)
                    {
                        printf("%s\n", comand_arr[i]);
                    }
                }
                break;
            
            default:
                printf("env: illegal option -- %s\n", temp);
                printf("usage: env [-iv] [-P utilpath] [-S string] [-u name]\n");
                printf("\t\tenv: option requires an argument -- u\n");
                return;
        }
    }
    


}

