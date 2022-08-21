#include "../inc/header.h"
void Comand_String(char *komand, char *final_string, char *komand_strig)
{
    int string_arr = 0;
    for(int i = 0; final_string[i] != '\0'; i++)
    {
                        
        if (final_string[i] == 96)
        {
            int k = i+1;
            for(; final_string[k] != 96 && final_string[k] != '\0' ; k++)
            {
                komand[k-i-1] = final_string[k];
            }
            i=k+1;
        }
 

    }
    for(;final_string[string_arr] != 96; string_arr++)
    {
        komand_strig[string_arr] = final_string[string_arr];

    }

}




