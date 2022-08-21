#include "../inc/header.h"

flags *mx_set_flags(char * argv, flags *old_flags)
{
    flags *new_flags = malloc(sizeof(flags));
    new_flags->flag_l = old_flags->flag_l;
    new_flags->flag_a = old_flags->flag_a;
    new_flags->flag_1 = old_flags->flag_1;
    new_flags->flag_C = old_flags->flag_C;
    new_flags->flag_m = old_flags->flag_m;
    new_flags->flag_p = old_flags->flag_p;

    new_flags->no_flags = old_flags->no_flags;

    int flags_amount = mx_strlen(argv);
    for (int i = 1; i < flags_amount; i++)
    {
        switch (argv[i])
        {
            case 's':
                new_flags->flag_l = i;
                new_flags->no_flags = 0;
                break;
            
            case 'P':
                new_flags->flag_a = i;
                new_flags->no_flags = 0;
                break;


            default:
                mx_printerr("uls: illegal option -- ");
                char tmp = argv[i];
                mx_printerr(&tmp);
                mx_printerr("\nusage: uls [-ACGRST@acefhlmprtu1] [file ...]\n");
                free(new_flags);
                new_flags = NULL;
                exit(1);
                break;
        }
    }

    return new_flags;
}

