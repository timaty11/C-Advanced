#include "../inc/header.h"


void RemoveChars(char *s, char c)
{
    int writer = 0, reader = 0;
    while (s[reader])
    {
        if (s[reader]!=c) 
        {   
            s[writer++] = s[reader];
        }
        reader++;       
    } 
    s[writer]=0;
}

