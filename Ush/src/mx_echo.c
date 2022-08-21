#include "../inc/header.h"


void mx_escape_seq_print(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == '\\')
        {
            i++;
            switch (str[i])
            {
                case 'a':
                    mx_printstr("\a");
                    break;

                case 'n':
                    mx_printstr("\n");
                    break;
                
                case 't':
                    mx_printstr("\t");
                    break;

                case 'v':
                    mx_printstr("\v");
                    break;

                case '\\':
                    mx_printstr("\\");
                    break;

                case '\'':
                    mx_printstr("\'");
                    break;
                
                case '\"':
                    mx_printstr("\"");
                    break;

                case '\?':
                    mx_printstr("\?");
                    break;

                
                default:
                    break;
            }
        }
        else
        {
            mx_printchar(str[i]);
        }
    }
}


void mx_echo(char *comand)
{
    if (comand[5] == '-' && comand[6] == 'n')
    {
        // If there is "
        if (comand[8] == 34) 
        {
            printf("%s\n", mx_strndup(&comand[9], mx_strlen(&comand[9]) - 1));
        }
        else // If there is no "
        {
            printf("%s\n", &comand[8]);
        }
    }
    else if (comand[5] == '-' && comand[6] == 'e')
    {
        // If there is "
        if (comand[8] == 34) 
        {
            char *without_quotes = mx_strndup(&comand[9], mx_strlen(&comand[9]) - 1);

            mx_escape_seq_print(without_quotes);
            mx_printchar('\n');
        }
        else // If there is no "
        {
            mx_escape_seq_print(&comand[8]);
            mx_printchar('\n');
        }
    }
    else 
    {
        system(comand);
    }
}

//// This things really work, but OROKOL didn't accept them in any way ////

// void mx_echo(char *comand)
// {
//     char **comand_arr = mx_strsplit(comand, ' ');
//     int comand_arr_size = mx_get_arr_size(comand_arr);

//     bool no_flags = true;
//     bool flag_n = false;
//     bool flag_e = false;
//     bool flag_E = false;

//     if (comand_arr_size == 1)
//     {
//         mx_printchar('\n');
//         return;
//     }
//     else
//     {
//         for (int i = 1; i < comand_arr_size; i++)
//         {
//             if (comand_arr[i][0] == '-')
//             {
//                 for (int j = 1; j < mx_strlen(comand_arr[i]); j++)
//                 {
//                     switch (comand_arr[i][j])
//                     {
//                         case 'n':
//                             flag_n = 1;
//                             no_flags = 0;
//                             break;
                        
//                         case 'e':
//                             flag_e = 1;
//                             no_flags = 0;
//                             break;

//                         case 'E':
//                             flag_E = 1;
//                             no_flags = 0;
//                             break;
                    
                    
//                         default:
//                             while (i < comand_arr_size)
//                             {
//                                 mx_printstr(comand_arr[i]);
//                                 mx_printchar(' ');
//                                 i++;
//                             }
//                             mx_printchar('\n');
                            
//                             return;
//                     }
//                 }
//             }
//             else
//             {
//                 // ЗАКОНЧИЛИ С ФЛАГАМИ ДАЛЬШЕ ПЕРЕБИРАЕМ КАЖДОЕ СЛОВО В КОМАНД_АРР
//                 for (int word = i; word < comand_arr_size; word++)
//                 {
//                     // СМОТРИМ ОТДЕЛЬНО КАЖДУЮ БУКВУ В КОМАНД_АРР
//                     for (int letter = 0; letter < mx_strlen(comand_arr[word]); letter++)
//                     {
//                         // ЕСЛИ НАША БУКВА ЭТО ДОЛЛАР А ДАЛЬШЕ СТОИТ ( ИЛИ { ТО ЭТО
//                         // КАКАЯ-ТО КОМАНДА И НАДО ЕЕ ВЫПОЛНИТЬ
//                         if (comand_arr[word][letter] == '$' && (comand_arr[word][letter + 1] == '(' || comand_arr[word][letter + 1] == '{'))
//                         { 
//                             char *command_dollar = mx_strnew(mx_strlen(comand_arr[word]) - 2);
//                             int z = letter + 2;
//                             int u = -1;
//                             for (; comand_arr[word][z] != '\0' && (comand_arr[word][z] != ')' && comand_arr[word][z] != '}'); z++)
//                             {
//                                 command_dollar[u] = comand_arr[word][z];
//                                 u++;
//                             }

//                             letter = z;

//                             system(command_dollar -1);

//                             // mx_printstr("\033[A"); // КУРСОР ВВЕРХ
//                             // mx_printstr("\033[C"); // КУРСОР ВПРАВО
//                             // mx_printstr("\033[D"); // КУРСОР ВЛЕВО
                            
//                         }
//                         else
//                         {
//                             mx_printchar(comand_arr[word][letter]);
//                         }
//                     }
//                     if (word + 2 != comand_arr_size)
//                     {
//                         mx_printchar(' ');
//                     }
//                 }

//                 return;
//             }
//         }
//     }
// }

