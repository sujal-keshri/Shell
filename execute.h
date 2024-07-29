#ifndef __EXECUTE_H_
#define __EXECUTE_H_

#include "headers.h"

typedef struct ex_return ex_return;
struct ex_return
{
    char* previous_directory;
    char* command_name;
    double ex_time;
};

void execute_sys_command(char* arg_0, char** args, int bg);
char *execute_command(char *home, char *previous_directory, char *command, ptrnode head, int bg);
ex_return execute_commands(char* home, char* previous_directory, char* input, ptrnode head, int is_past);

#endif