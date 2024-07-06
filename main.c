#include "headers.h"

int main()
{
    char* home=pwd();
    char* previous_directory="OLD DIRECTORY NOT SET";
    // printf("%s\n", home);

    // Keep accepting commands
    while (1)
    {
        // Print appropriate prompt with username, systemname and directory before accepting input
        prompt(home);
        char input[4096];
        fgets(input, 4096, stdin);
        
        int inp_len=strlen(input);
        if(input[inp_len-1]=='\n')
            input[inp_len-1]='\0';

        char token_input[4096];
        strcpy(token_input, input);
        char *command = strtok(token_input, " ");
        
        if(strcmp(command, "warp")==0)
        {
            previous_directory=warp(home, previous_directory, input);
        }

        else if (strcmp(command, "peek")==0)
        {
            peek(home, previous_directory, input);
        }

        else if (strcmp(command, "proclore")==0)
        {
            int p=getpid();
            proclore(home, input, p);
        }
    }
}
