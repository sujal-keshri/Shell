#include "warp.h"

char *warp(char *home, char *previous_directory, char *command)
{
    char *path = strtok(command, " ");
    path = strtok(NULL, " ");
    if (path == NULL)
    {
        if (chdir(home) == 0)
        {
            printf("%s\n", home);
            previous_directory = home;
        }

        else
            perror("Error");
    }

    while (path != NULL)
    {
        char *curr_dir = pwd();
        if (strcmp(path, "~") == 0 || strcmp(path, "") == 0)
        {
            if (chdir(home) == 0)
            {
                printf("%s\n", home);
                previous_directory = curr_dir;
            }

            else
                perror("Error");
        }

        else if (path[0] == '~')
        {
            char temp[1000];
            strcpy(temp, home);
            strncat(temp, path + 1, strlen(path));

            if (chdir(temp) == 0)
            {
                printf("%s\n", temp);
                previous_directory = curr_dir;
            }

            else
                perror("Error");
        }

        else if (strcmp(path, "-") == 0)
        {
            if (strcmp(previous_directory, "OLD DIRECTORY NOT SET") == 0)
                printf("%s\n", "OLD DIRECTORY NOT SET");

            else if (chdir(previous_directory) == 0)
            {
                printf("%s\n", previous_directory);
                previous_directory = curr_dir;
            }

            else
                perror("Error");
        }

        else
        {
            int path_len = strlen(path);
            if (chdir(path) == 0)
            {
                printf("%s\n", pwd());
                previous_directory = curr_dir;
            }

            else
            {
                perror("Error");
            }
        }
        path = strtok(NULL, " ");
    }
    return previous_directory;
}