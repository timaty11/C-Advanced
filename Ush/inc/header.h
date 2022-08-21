#ifndef HEADER_H
#define HEADER_H
#define SIGCONT 19

#include <libmx.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>


typedef struct flags {
    int no_flags;
    int flag_l;
    int flag_a;
    int flag_1; // (the number 1)
    int flag_C;
    int flag_m;
    int flag_p;
}              flags;

typedef struct s_flags_which
{
    bool using_A;
    bool using_S;
}              t_flags_which;

typedef struct stopped_process
{
    int id;
    pid_t child_pid;
    struct stopped_process *next;
}              stopped_process;

typedef struct env_var_names
{
    char var_name[256];
    struct env_var_names *next;
}              env_var_names;


pid_t cpid;

flags *mx_set_flags(char * argv, flags *flags);


void mx_unset(char *comand);
void mx_pwd(char *comand);
void mx_cd(char *comand, char *home_dir, char *pasr_dir);
void mx_echo(char *comand);
void mx_escape_seq_print(char *str);
void mx_which(char *comand);
void mx_export(char *comand, env_var_names **head);
void mx_unset(char *comand);

void mx_signum_handler(int signum);
void synch_signal();

void mx_env(char *comand, env_var_names *List_var_names_head);
int sortanul(env_var_names **head, char *to_find);
void mx_fg(char *comand, stopped_process *List_head);
void RemoveChars(char *s, char c);
void Comand_String(char *komand, char *final_string, char *komand_strig);

stopped_process *mx_node_create(int id, pid_t pid);
stopped_process *mx_add_element(stopped_process **head, pid_t pid);

env_var_names *mx_names_create(char *name);
env_var_names *mx_add_name_element(env_var_names **head, char *name);
void mx_del_name_node(env_var_names **head, char *name);


#endif
