#include "pastevents.h"


char* get_nth_command(int n)
{
    char path[512];
    strcpy(path, home);
    strcat(path, "/history.txt");
    char* command=(char*)malloc(sizeof(char)*4096);
    FILE *fin = fopen(path, "r");
    if (fin != NULL)
    {
        int n_commands = 0;
        char commands[15][4096];
        while (fgets(commands[n_commands], sizeof(commands[n_commands]), fin) != NULL)
        {
            n_commands++;
        }
        if(n_commands-n>=0)
            strcpy(command, commands[n_commands-n]);
        else
            strcpy(command, "No corresponding command present\n");
    }
    else
        strcpy(command, "No corresponding command present\n");

    command[strlen(command)-1]='\0';
    return command;
}

void save_history(char *command)
{
    char path[512];
    strcpy(path, home);
    strcat(path, "/history.txt");

    strcat(command, "\n");
    FILE *fin = fopen(path, "r");
    if (fin != NULL)
    {
        int n_commands = 0;
        char commands[15][4096];
        while (fgets(commands[n_commands], sizeof(commands[n_commands]), fin) != NULL)
        {
            n_commands++;
        }
        fclose(fin);
        if (strcmp(command, commands[n_commands - 1]) != 0)
        {
            FILE *fout = fopen(path, "w");
            int start = n_commands == 15 ? 1 : 0;
            for (int i = start; i < n_commands; i++)
            {
                fputs(commands[i], fout);
            }
            fputs(command, fout);
            fclose(fout);
        }
    }
    else
    {
        FILE *fout = fopen(path, "w");
        fputs(command, fout);
        fclose(fout);
    }
}

void display_history()
{
    char path[512];
    strcpy(path, home);
    strcat(path, "/history.txt");
    FILE *fin = fopen(path, "r");
    if(fin!=NULL)
    {
        char buff[4096];
        while (fgets(buff, sizeof(buff), fin) != NULL)
            printf("%s", buff);
    }
    fclose(fin);
}

void delete_entries()
{
    char path[512];
    strcpy(path, home);
    strcat(path, "/history.txt");
    FILE* f=fopen(path, "w");
    fclose(f);
}