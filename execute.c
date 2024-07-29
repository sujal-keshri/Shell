#include "execute.h"

void execute_sys_command(char *arg_0, char **args, int bg)
{
    int child_id = fork();
    if (child_id == 0)
    {
        if (execvp(arg_0, args) == -1)
        {
            printf("ERROR : '%s' is not a valid command\n", arg_0);
            exit(1);
        }
    }
    else if (child_id > 0)
    {
        fg_running_flag = 1;
        if (bg == 0)
            foreground_pid = child_id;
        int status;
        waitpid(child_id, &status, 0);
        fg_running_flag = 0;
        if (bg == 0)
            foreground_pid = 0;
    }

    return;
}

char *execute_command(char *home, char *previous_directory, char *command, ptrnode head, int bg)
{
    char temp_command[512];
    strcpy(temp_command, command);

    char *args[64];
    int arg_c = 0;

    char *arg = strtok(temp_command, " ");
    while (arg != NULL)
    {
        args[arg_c++] = arg;
        arg = strtok(NULL, " ");
    }
    args[arg_c] = NULL;

    if (strcmp(args[0], "warp") == 0)
    {
        previous_directory = warp(home, previous_directory, command);
    }

    else if (strcmp(args[0], "peek") == 0)
    {
        peek(home, previous_directory, command);
    }

    else if (strcmp(args[0], "proclore") == 0)
    {
        int p = getpid();
        proclore(home, command, p);
    }

    else if (strcmp(args[0], "seek") == 0)
    {
        seek(home, previous_directory, command);
    }

    else if (strcmp(args[0], "iMan") == 0)
    {
        if (arg_c == 2)
            iman(args[1]);
        else
            printf("One argument required\n");
    }

    else if (strcmp(args[0], "activities") == 0)
    {
        print_processes(head);
    }

    else if (strcmp(args[0], "ping") == 0)
    {
        if (arg_c == 3)
            send_signal(args[1], args[2]);
        else
            printf("Two arguments required\n");
    }

    else if (strcmp(args[0], "neonate") == 0)
    {
        if(arg_c==3 && strcmp(args[1], "-n")==0)
            neonate_exe(args[2]);
        else
            printf("Incorrect format\n");
    }

    else if (strcmp(args[0], "fg") == 0)
    {
        if (arg_c == 2)
            back_to_fore(args[1]);
        else
            printf("One argument required\n");
    }

    else if (strcmp(args[0], "bg") == 0)
    {
        if (arg_c == 2)
            back_stop_to_running(args[1]);
        else
            printf("One argument required\n");
    }

    else if (strcmp(args[0], "pastevents") == 0)
    {
        if (arg_c == 1)
            display_history();
        else if (arg_c == 2 && strcmp(args[1], "purge") == 0)
            delete_entries();
        else if (arg_c == 3 && strcmp(args[1], "execute") == 0)
        {
            char *past_command = get_nth_command(atoi(args[2]));
            previous_directory = execute_commands(home, previous_directory, past_command, head, 1).previous_directory;
            free(past_command);
        }
        else
            printf("Invalid command\n");
    }

    else
        execute_sys_command(args[0], args, bg);

    return previous_directory;
}

ex_return execute_commands(char *home, char *previous_directory, char *input, ptrnode head, int is_past) // is_past=1 for pastevents_execute and 0 otherwise
{
    FILE *out_file_ptr;
    int in_change_flag = 0;
    int out_change_flag = 0;
    time_t start_t, end_t;
    double ex_time;
    char temp_input[4096];
    strcpy(temp_input, input);
    st_tokens command = tokenize(temp_input);
    char **tokens = command.tokens;
    int n_commands = command.n_commands;
    char *symbols = symbol_str(input);
    char *command_0;
    char history_command[4096];
    strcpy(history_command, "");
    int pastevents_flag = 0;
    for (int i = 0; i < n_commands; i++)
    {
        char temp_token_for_past[4096];
        strcpy(temp_token_for_past, tokens[i]);
        io_return check_io = check_and_redirect(tokens[i]);
        if (check_io.in_flag == 1 || check_io.out_flag != 0)
        {
            strcpy(tokens[i], check_io.command_part);
            if (check_io.in_flag == 1)
            {
                char in_file[100];
                strcpy(in_file, check_io.in_file);
                strcat(tokens[i], " ");
                strcat(tokens[i], in_file);
                in_change_flag = 1;
            }
            if (check_io.out_flag != 0)
            {
                char out_file[100];
                strcpy(out_file, check_io.out_file);

                if (check_io.out_flag == 1)
                    out_file_ptr = fopen(out_file, "a");
                else if (check_io.out_flag == 2)
                    out_file_ptr = fopen(out_file, "w");

                if (freopen(out_file, "a", stdout) == NULL)
                    perror("freopen");

                out_change_flag = 1;
            }
        }
        char temp_token[4096];
        strcpy(temp_token, tokens[i]);
        command_0 = strtok(temp_token, " ");
        if (symbols[i] == '&')
        {
            int new_process_id = fork();
            if (new_process_id == 0)
            {
                previous_directory = execute_command(home, previous_directory, tokens[i], head, 1);
                exit(EXIT_SUCCESS);
            }
            else
            {
                printf("%d\n", new_process_id);
                insert_process(head, new_process_id, command_0, 1);
            }
        }
        else
        {
            start_t = time(NULL);
            previous_directory = execute_command(home, previous_directory, tokens[i], head, 0);
            end_t = time(NULL);
            ex_time = end_t - start_t;
        }

        if (out_change_flag == 1)
        {
            fclose(out_file_ptr);

            if (freopen("/dev/tty", "w", stdout) == NULL)
                perror("freopen");

            out_change_flag = 0;
        }
        if (in_change_flag == 1)
            in_change_flag = 0;

        if (strcmp(temp_token_for_past, "pastevents") == 0 || strcmp(temp_token_for_past, "pastevents purge") == 0)
            pastevents_flag = 1;

        if (strstr(temp_token_for_past, "pastevents execute") != NULL)
        {
            char *n = strtok(temp_token_for_past, " ");
            n = strtok(NULL, " ");
            n = strtok(NULL, " ");
            char *past_command = get_nth_command(atoi(n));
            strcpy(temp_token_for_past, past_command);
            free(past_command);
        }
        
        if (strlen(history_command) != 0)
            strcat(history_command, " ");

        char temp_s[512];
        if (symbols[i] == '\0')
            strcat(history_command, temp_token_for_past);
        else
        {
            snprintf(temp_s, sizeof(temp_s), "%s %c", temp_token_for_past, symbols[i]);
            strcat(history_command, temp_s);
        }
    }
    if (pastevents_flag == 0 && is_past == 0)
        save_history(history_command);

    ex_return info;
    info.previous_directory = previous_directory;
    info.command_name = command_0;
    info.ex_time = ex_time;

    return info;
}