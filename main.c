#include "headers.h"

int foreground_pid=0;
char* home;
char prompt_input[50];
int fg_running_flag=0;
ptrnode head;

int main()
{
    signal(SIGINT, ctrl_c_func);
    home = pwd();
    char *previous_directory = "OLD DIRECTORY NOT SET";

    head = init_list();
    // Keep accepting commands
    // char prompt_input[50];
    strcpy(prompt_input, "");
    while (1)
    {
        // Print appropriate prompt with username, systemname and directory before accepting input
        prompt(home, prompt_input);
        char input[4096];
        if(fgets(input, 4096, stdin)==NULL)
        {
            char exit_for_history[5]="exit";
            save_history(exit_for_history);
            kill_all_processes(head);
            printf("\n");
            exit(EXIT_SUCCESS);
        }

        if (input[0] == '\n')
            continue;

        int inp_len = strlen(input);
        if (input[inp_len - 1] == '\n')
            input[inp_len - 1] = '\0';

        search_and_delete(head);

        ex_return info = execute_commands(home, previous_directory, input, head, 0);
        previous_directory=info.previous_directory;
        if(info.ex_time>2)
        {
            int time=(int)info.ex_time;
            snprintf(prompt_input, sizeof(prompt_input), " %s : %ds", info.command_name, time);
        }
        else
            strcpy(prompt_input, "");
    }
}
