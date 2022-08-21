#include "../inc/header.h"

//// Stable version ////


void mx_cd(char *comand, char *home_dir, char *pasr_dir)
{
    char **comand_arr = mx_strsplit(comand, ' ');
    int comand_arr_size = mx_get_arr_size(comand_arr);

    if (comand_arr_size > 3)
    {
        mx_printerr("cd: too many arguments\n");
        return;
    }

    char *dir_to_check = mx_strnew(256);
    bool found_dir_to_check = false;

    if (comand_arr_size == 1) // If there is just cd go to home dir
    {
        char cwd[1024];
        getcwd(cwd, sizeof(cwd));
        setenv("OLDPWD", cwd, 1);

        chdir(home_dir);
        setenv("PWD", home_dir, 1);
    }
    else // if there is cd and something else
    {
        bool no_flags = 1;
        bool flag_P = 0;
        bool flag_L = 0;
        bool flag_defiz = 0;

        // If there is flag, it can be something like this:
        // cd -LP dir1 OR cd -L -P dir1
        // That's why we start cycle to check all of the elements

        for (int i = 1; i < comand_arr_size; i++)
        {
            if (comand_arr[i][0] == '-')
            {
                // If the flag is just -
                if (mx_strlen(comand_arr[i]) == 1)
                {
                    flag_defiz = 1;
                    no_flags = 0;
                    continue;
                }

                for (int j = 1; j < mx_strlen(comand_arr[i]); j++)
                {
                    switch (comand_arr[i][j])
                    {
                        case 'P':
                            flag_P = 1;
                            no_flags = 0;
                            break;
                        
                        case 'L':
                            flag_L = 1;
                            no_flags = 0;
                            break;
                    
                    
                        default:
                            mx_printerr("cd: no such file or directory: ");
                            mx_printerr(comand_arr[i]);
                            mx_printerr("\n");
                            break;
                    }
                }
            }
            else
            {
                if (!found_dir_to_check)
                {
                    mx_strcpy(dir_to_check, comand_arr[i]);
                    found_dir_to_check = true;
                }
                else if (found_dir_to_check)
                {
                    mx_printerr("cd: string not in pwd: ");
                    mx_printerr(dir_to_check);
                    mx_printerr("\n");
                }
            }
        }

        if (!found_dir_to_check)
        {
            mx_strcpy(dir_to_check, home_dir);
        }

        // If we something that is not a - then there must dirs 

        if (flag_defiz != 0)
        {
            // If the flag is - we need to go to previous path

            char *temp_pwd = mx_strdup(getenv("PWD"));
            chdir(getenv("OLDPWD"));
            setenv("OLDPWD", temp_pwd, 1);

            char cwd_new[1024];
            getcwd(cwd_new, sizeof(cwd_new));
            setenv("PWD", cwd_new, 1);
        }
        else if (flag_L != 0)
        {
            // This flag will go to dir and write shortes path with links

            char cwd_ne_ssilka[1024];
            getcwd(cwd_ne_ssilka, sizeof(cwd_ne_ssilka));
            if (mx_strlen(cwd_ne_ssilka) != 1)
            {
                mx_strcat(cwd_ne_ssilka, "/");
            }
            mx_strcat(cwd_ne_ssilka, dir_to_check);

            chdir(cwd_ne_ssilka);
            setenv("PWD", cwd_ne_ssilka, 1);
        }
        else if (flag_P != 0)
        {
            // This flag will go to dir and write full path even if there are links

            struct stat info;
            
            if (lstat(dir_to_check, &(info)) == -1) {
                perror("lstat");
                exit(EXIT_FAILURE);
            }
            if ((((info.st_mode) & S_IFMT) == S_IFLNK))
            {
                char cwd_ssilka[1024];
                getcwd(cwd_ssilka, sizeof(cwd_ssilka));

                ssize_t buf_size = info.st_size == 0 ? 100 : info.st_size + 1;
                char *buf = mx_strnew(buf_size);
                ssize_t nbytes = readlink(dir_to_check, buf, buf_size);

                if (nbytes >= 0) {
                    mx_strcat(cwd_ssilka, buf);
                }
                mx_strdel(&buf);
              
                chdir(cwd_ssilka);
                setenv("PWD", cwd_ssilka, 1);
            }
            else if ((((info.st_mode) & S_IFMT) == S_IFDIR))
            {
                DIR *temp_dir = opendir(dir_to_check);
                if (temp_dir == NULL)
                {
                    printf("cd: no such file or directory: %s\n", dir_to_check);
                }
                else
                {
                    chdir(dir_to_check);
                    char cwd_ne_ssilka[1024];
                    getcwd(cwd_ne_ssilka, sizeof(cwd_ne_ssilka));
                    setenv("PWD", cwd_ne_ssilka, 1);
                    closedir(temp_dir);
                }
            }
        }
        else if (no_flags != 0)
        {
            if (dir_to_check[0] == '~')
            {
                char cwd[1024];
                getcwd(cwd, sizeof(cwd));
                setenv("OLDPWD", cwd, 1);

                chdir(home_dir);
                setenv("PWD", home_dir, 1);

                return;
            }

            // If there are no flags then just go to dir user has entered

            mx_strcpy(pasr_dir, dir_to_check);
            
            // If dir does not open print an error

            DIR *temp_dir = opendir(dir_to_check);
            if (temp_dir == NULL)
            {
                printf("cd: no such file or directory: %s\n", dir_to_check);
            }
            
            else 
            {
                // If User entered / then go to root dir

                if (dir_to_check[0] == '/')
                {
                    // Write cur pwd into OLDPW
                    setenv("OLDPWD", getenv("PWD"), 1);
                    
                    // Go to root dir
                    chdir(dir_to_check);

                    // Update cur pwd
                    setenv("PWD", dir_to_check, 1);
                    closedir(temp_dir);
                    return;
                }
                else if (!mx_strcmp(dir_to_check, "./"))
                {
                    return;
                }
                // Go to dir up
                else if (!mx_strcmp(dir_to_check, "../"))
                {
                    // Write cur pwd into OLDPW
                    setenv("OLDPWD", getenv("PWD"), 1);
                    chdir(dir_to_check);

                    char *new_pwd = mx_strdup(getenv("PWD"));
                    for (int i = mx_strlen(new_pwd); i >= 0 && new_pwd[i] != '/'; i--)
                    {
                        new_pwd[i] = '\0';
                    }
                    new_pwd[mx_strlen(new_pwd) - 1] = '\0';
                    setenv("PWD", new_pwd, 1);

                    closedir(temp_dir);
                    return;
                }

                char cwd[1024];
                getcwd(cwd, sizeof(cwd));
                setenv("OLDPWD", cwd, 1);

                chdir(dir_to_check);
                char cwd_ne_ssilka[1024];
                getcwd(cwd_ne_ssilka, sizeof(cwd_ne_ssilka));
                setenv("PWD", cwd_ne_ssilka, 1);
                closedir(temp_dir);
            }
        }
    }

    return;
}

