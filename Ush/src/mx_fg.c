#include "../inc/header.h"


void mx_fg(char *comand, stopped_process *List_head)
{
    char **comand_arr = mx_strsplit(comand, ' ');
    int comand_arr_size = mx_get_arr_size(comand_arr);

    if(comand_arr_size > 1)
    {
        mx_printstr("fg: job not found: ");
        mx_printstr(comand_arr[1]); 
        mx_printstr("\n");
    }
    else
    {
        printf("BLYA BLYA %i\n", List_head->next->child_pid);
        int hyi = kill(List_head->next->child_pid, SIGCONT);
        if (hyi == -1) {
            perror("kill");
            exit(EXIT_FAILURE);
        }
    }
}

