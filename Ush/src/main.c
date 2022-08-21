#include "../inc/header.h"

/* When a SIGUSR1 signal arrives, set this variable. */
volatile sig_atomic_t usr_interrupt = 0;

void synch_signal()
{
    usr_interrupt = 1;
}

int main (int argc, char * argv[], char **envp)
{
    stopped_process *List_head = mx_node_create(0, getpid());
    env_var_names *List_var_names_head = mx_names_create("hyi");
    
    for (int i = 0; envp[i] != NULL; i++)
    {
        char **envp_arr = mx_strsplit(envp[i], '=');
        mx_add_name_element(&List_var_names_head, envp_arr[0]);
        mx_del_strarr(&envp_arr);
    }

    signal(SIGINT, mx_signum_handler);
    signal(SIGQUIT, mx_signum_handler);

    struct sigaction usr_action;
    sigset_t block_mask;

    /* Establish the signal handler. */
    sigfillset(&block_mask);
    usr_action.sa_handler = synch_signal;
    usr_action.sa_mask = block_mask;
    usr_action.sa_flags = 0;
    sigaction(SIGTSTP, &usr_action, NULL);
    
    // ЧТОБ НЕ РУГАЛОСЬ НА АРГВ АРГС
    char *arr = mx_file_to_str(argv[1]);
    arr = NULL;

    // Cur dir
    char *pasr_dir = (char *)malloc(sizeof(char)*100); 
    
    char *comand = (char *)malloc(sizeof(char) * 256);
    for (int i = 0; i < 256; i++)
    {
        comand[i] = '\0';
    }
    char *home_dir = (char *)malloc(sizeof(char)*256);
    mx_strcpy(home_dir, "/Users/");
    mx_strcat(home_dir, getlogin());

    if (argc != 1)
    {
        printf("Viidi i zaidi normalno");
        return 1;
    }

    while(!feof(stdin))
    {
    //    printf("u$h> "); //??????????????????????????
        
        if (fgets(comand, 256, stdin) == NULL)
        {
            continue;
        }
        comand[mx_strlen(comand) - 1] = '\0';

        char **comand_arr = mx_strsplit(comand, ';');
        int comand_arr_size = mx_get_arr_size(comand_arr);
        if (comand_arr_size > 1)
        {
            for (int i = 0; i < comand_arr_size; i++)
            {
                if (comand_arr[i][0] == ' ')
                {
                    char *temp = &comand_arr[i][1];
                    comand_arr[i] = mx_strdup(temp);
                }
                if (comand_arr[i][mx_strlen(comand_arr[i]) - 1] == ' ')
                {
                    comand_arr[i][mx_strlen(comand_arr[i]) - 1] = '\0';
                }
            }
        }

        for (int i = 0; i < comand_arr_size; i++)
        {
            if ((comand_arr[i][0] == 'p' && comand_arr[i][2] == 'd') ) // pwd
            {
                mx_pwd(comand_arr[i]);
            }
            else if (comand_arr[i][0] == 'c' && comand_arr[i][1] == 'd') // cd
            {
                mx_cd(comand_arr[i], home_dir, pasr_dir);
            }
            else if (comand_arr[i][0] == 'e' && comand_arr[i][2] == 'h') //echo 
            {
                mx_echo(comand_arr[i]);
            }
            else if (comand_arr[i][0] == 'w' && comand_arr[i][2] == 'i') // which <
            {
                mx_which(comand_arr[i]);
            }
            else if (comand_arr[i][0] == 'e' && comand_arr[i][1] == 'n' && comand_arr[i][2]== 'v') // env  < -- сука
            {
                mx_env(comand_arr[i], List_var_names_head);
                // system("env");
            }
            else if (comand_arr[i][0] == 'e' && comand_arr[i][1] == 'x' && comand_arr[i][5]== 't') // export
            {
                // system(comand_arr[i]);
                mx_export(comand_arr[i], &List_var_names_head);
            }
            else if (comand_arr[i][0] == 'u' && comand_arr[i][1] == 'n' && comand_arr[i][4]== 't') // unset
            {
                mx_unset(comand_arr[i]);
            }
            else if (comand_arr[i][0] == 'f' && comand_arr[i][1] == 'g' )
            {
                mx_fg(comand_arr[i], List_head);
            }
            else if (comand_arr[i][0] == 'h' && comand_arr[i][1] == 'y' && comand_arr[i][2] == 'i') //// TEMP COMAND
            {
                cpid = fork();
                if (cpid == -1) {
                    perror("fork");
                    exit(EXIT_FAILURE);
                }
                
                mx_add_element(&List_head, cpid);

                if (cpid == 0) {    /* Child */
                    signal(SIGTSTP, mx_signum_handler);
                    while (1)
                    {
                        mx_printstr("hyi | ");
                        sleep(1);
                    }
                }
                else    /* Parent */
                {
                    while(!usr_interrupt)
                    {
                        sleep(1);
                    }
                    
                    usr_interrupt = 0;
                }
            }
            else if (!mx_strcmp(comand_arr[i], "exit"))
            {
                return 1; 
            }
        }
    }

    // printf("\n[Process completed]");
    return 0;
}

