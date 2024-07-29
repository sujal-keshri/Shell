#include "seek.h"

// flag_e---> 0-> e not applicable, 1->no file/dir found, 2->one file/dir found, 3->more than one file/dir found
int flag_e = 0;
char f_d[256];

int search_dir_file(char *home, char *original_target_path, char *target_path, char *f_d_name, int flag, int found)
{
    if (strcmp(original_target_path, "~") == 0)
    {
        strcpy(original_target_path, home);
        strcpy(target_path, home);
    }

    else if (original_target_path[0] == '~')
    {
        char temp[1000];
        strcpy(temp, home);
        strncat(temp, original_target_path + 1, strlen(original_target_path));
        strcpy(original_target_path, temp);
        strcpy(target_path, temp);
    }

    DIR *dir = opendir(target_path);
    if (dir == NULL)
    {
        perror("Error opening directory");
        return found;
    }

    struct dirent *entry;
    entry = readdir(dir);
    while (entry != NULL)
    {
        char fullPath[1000];
        strcpy(fullPath, target_path);
        strcat(fullPath, "/");
        strcat(fullPath, entry->d_name);

        struct stat f_d_stat;
        if (lstat(fullPath, &f_d_stat) == -1)
        {
            perror("Error stat-ing file");
            continue;
        }
        char temp_path[1000];
        strcpy(temp_path, entry->d_name);
        char *optional_path = strtok(temp_path, ".");
        if (S_ISDIR(f_d_stat.st_mode))
        {
            if (strcmp(entry->d_name, f_d_name) == 0 && flag != 2)
            {
                found = 1;
                if (flag_e == 0)
                {
                    int dir_len = strlen(original_target_path);
                    printf(BLUE_COLOR "." RESET_COLOR);
                    int i = dir_len;
                    while (target_path[i] != '\0')
                        printf(BLUE_COLOR "%c" RESET_COLOR, target_path[i++]);
                    printf(BLUE_COLOR "/%s\n" RESET_COLOR, f_d_name);
                }

                else if (flag_e == 1)
                {
                    strcpy(f_d, fullPath);
                    flag_e = 2;
                }
                else if (flag_e == 2)
                {
                    flag_e = 3;
                    closedir(dir);
                    return found;
                }
                else if (flag_e == 3)
                {
                    closedir(dir);
                    return found;
                }
            }
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
                found = search_dir_file(home, original_target_path, fullPath, f_d_name, flag, found);
        }
        else if (S_ISREG(f_d_stat.st_mode))
        {
            if ((strcmp(entry->d_name, f_d_name) == 0 || strcmp(optional_path, f_d_name) == 0) && flag != 1)
            {
                found = 1;
                if (flag_e == 0)
                {
                    int dir_len = strlen(original_target_path);
                    printf(GREEN_COLOR "." RESET_COLOR);
                    int i = dir_len;
                    while (target_path[i] != '\0')
                        printf(GREEN_COLOR "%c" RESET_COLOR, target_path[i++]);

                    printf(GREEN_COLOR "/%s\n" RESET_COLOR, entry->d_name);
                }
                else if (flag_e == 1)
                {
                    strcpy(f_d, fullPath);
                    flag_e = 2;
                }
                else if (flag_e == 2)
                {
                    flag_e = 3;
                    return found;
                }
                else if (flag_e == 3)
                {
                    closedir(dir);
                    return found;
                }
            }
        }
        entry = readdir(dir);
    }

    closedir(dir);
    return found;
}

void seek(char *home, char *previous_directory, char *command)
{
    char *d = strstr(command, "-d");
    char *f = strstr(command, "-f");
    char *e = strstr(command, "-e");

    char target_dir[1000];
    char f_d_name[1000];
    int found;


    if (d == NULL && f == NULL && e == NULL)
    {
        strcpy(f_d_name, strtok(command, " "));
        strcpy(f_d_name, strtok(NULL, " "));
        char *temp = strtok(NULL, " ");
        temp == NULL ? strcpy(target_dir, ".") : strcpy(target_dir, temp);
        found = search_dir_file(home, target_dir, target_dir, f_d_name, 0, 0);
    }

    else if (d != NULL && f != NULL)
        printf("Invalid flags!\n");

    else if (d != NULL && e == NULL)
    {
        strcpy(f_d_name, strtok(command, " "));
        strcpy(f_d_name, strtok(NULL, " "));
        strcpy(f_d_name, strtok(NULL, " "));
        char *temp = strtok(NULL, " ");
        temp == NULL ? strcpy(target_dir, ".") : strcpy(target_dir, temp);
        found = search_dir_file(home, target_dir, target_dir, f_d_name, 1, 0);
    }

    else if (f != NULL && e == NULL)
    {
        strcpy(f_d_name, strtok(command, " "));
        strcpy(f_d_name, strtok(NULL, " "));
        strcpy(f_d_name, strtok(NULL, " "));
        char *temp = strtok(NULL, " ");
        temp == NULL ? strcpy(target_dir, ".") : strcpy(target_dir, temp);
        found = search_dir_file(home, target_dir, target_dir, f_d_name, 2, 0);
    }

    else if (e != NULL && d == NULL && f == NULL)
    {
        flag_e = 1;
        strcpy(f_d_name, strtok(command, " "));
        strcpy(f_d_name, strtok(NULL, " "));
        strcpy(f_d_name, strtok(NULL, " "));
        char *temp = strtok(NULL, " ");
        temp == NULL ? strcpy(target_dir, ".") : strcpy(target_dir, temp);
        found = search_dir_file(home, target_dir, target_dir, f_d_name, 0, 0);
    }

    else if (e != NULL && d != NULL)
    {
        flag_e = 1;
        strcpy(f_d_name, strtok(command, " "));
        strcpy(f_d_name, strtok(NULL, " "));
        strcpy(f_d_name, strtok(NULL, " "));
        strcpy(f_d_name, strtok(NULL, " "));
        char *temp = strtok(NULL, " ");
        temp == NULL ? strcpy(target_dir, ".") : strcpy(target_dir, temp);
        found = search_dir_file(home, target_dir, target_dir, f_d_name, 1, 0);
    }

    else if (e != NULL && f != NULL)
    {
        flag_e = 1;
        strcpy(f_d_name, strtok(command, " "));
        strcpy(f_d_name, strtok(NULL, " "));
        strcpy(f_d_name, strtok(NULL, " "));
        strcpy(f_d_name, strtok(NULL, " "));
        char *temp = strtok(NULL, " ");
        temp == NULL ? strcpy(target_dir, ".") : strcpy(target_dir, temp);
        found = search_dir_file(home, target_dir, target_dir, f_d_name, 2, 0);
    }

    if (found == 0)
        printf("Not found!\n");

    if (flag_e == 2)
    {
        struct stat f_d_stat;
        if (lstat(f_d, &f_d_stat) == -1)
        {
            perror("Error stat-ing file");
        }

        if (S_ISDIR(f_d_stat.st_mode))
        {
            if (access(f_d, X_OK) == 0)
            {
                char input[1000];
                strcpy(input, "warp ");
                strcat(input, f_d);
                warp(home, previous_directory, input);
            }
            else
                printf("Missing permissions for task!\n");
        }
        else if (S_ISREG(f_d_stat.st_mode))
        {
            if (access(f_d, R_OK) == 0)
            {
                int dir_len = strlen(target_dir);
                printf(GREEN_COLOR "." RESET_COLOR);
                int i = dir_len;
                while (f_d[i] != '\0')
                    printf(GREEN_COLOR "%c" RESET_COLOR, f_d[i++]);
                printf("\n");

            }
            else
                printf("Missing permissions for task!\n");
        }
    }
    flag_e = 0;
}
