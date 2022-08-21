#include "../inc/header.h"

stopped_process *mx_node_create(int id, pid_t pid) {
    stopped_process *node = (stopped_process *)malloc(sizeof(stopped_process));
    node->id = id;
    node->child_pid = pid;
    node->next = NULL;
    
    return node;
}


stopped_process *mx_add_element(stopped_process **head, pid_t pid) {
    int id = 0;
    stopped_process *tmp = *head;
    while (tmp->next)
    {
        tmp = tmp->next;
        id++;
    }
    tmp->next = mx_node_create(id, pid);

    return tmp->next;
}


env_var_names *mx_names_create(char *name)
{
    env_var_names *node = (env_var_names *)malloc(sizeof(env_var_names));
    for (int i = 0; i < 256; i++)
    {
        node->var_name[i] = '\0';
    }
    mx_strcpy(node->var_name, name);

    node->next = NULL;
    
    return node;
}


env_var_names *mx_add_name_element(env_var_names **head, char *name)
{
    env_var_names *tmp = *head;
    while (tmp->next)
    {
        tmp = tmp->next;
    }
    tmp->next = mx_names_create(name);

    return tmp->next;
}


void mx_del_name_node(env_var_names **head, char *name)
{
    env_var_names *tmp = *head;
    env_var_names *next_tmp = tmp->next;

    while (tmp != NULL && next_tmp != NULL)
    {
        if (!mx_strcmp(next_tmp->var_name, name))
        {
            for (int i = 0; i < 256; i++)
            {
                next_tmp->var_name[i] = '\0'; 
            }
            if (next_tmp->next == NULL)
            {
                tmp->next = NULL;
                return;
            }
            tmp->next = next_tmp->next;
            free(next_tmp);
        }

        tmp = tmp->next;
        next_tmp = tmp->next;
    }

}

