#include "../inc/header.h"


void mx_signum_handler(int signum) 
{
    switch (signum)
    {
        case SIGINT:
            mx_printstr("\nu$h> ");
            signal(SIGINT, SIG_IGN);
            break;

        case SIGTSTP:
            mx_printstr("\nu$h> HYI END - ");

            if (getpid() == 0)
            {
                kill(cpid, SIGTSTP);
                signal(SIGTSTP, SIG_IGN);
                exit(0);
            }
            

        default:
            break;
    }
}






