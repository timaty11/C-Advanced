#include "../inc/header.h"


int sortanul(env_var_names **head, char *to_find)
{
    env_var_names *node = *head;

    while (node != NULL)
    {
        char **temp = mx_strsplit(node->var_name, '=');
        if (!mx_strcmp(temp[0], to_find))
        {
            return 1;
        }

        node = node->next;
    }
    
    return 0;
}





