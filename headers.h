#ifndef HEADERS_H_
#define HEADERS_H_

//for utilities
typedef struct node node;
typedef node* ptrnode;
struct node
{
    int pid;
    char* command;
    int r_s_state;        // 1 for running, 0 for stopped
    struct node* next;
    struct node* last;
};

//for input_requirements
typedef struct st_tokens st_tokens;
struct st_tokens
{
    char** tokens;
    int n_commands;
};

//for I/O redirection
typedef struct io_return io_return;
struct io_return
{
    int in_flag;
    int out_flag;
    char in_file[100];
    char out_file[100];
    char command_part[512];
};

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>
#include <termios.h>

#include "utilities.h"
#include "prompt.h"
#include "pwd.h"
#include "warp.h"
#include "peek.h"
#include "proclore.h"
#include "seek.h"
#include "input_requirement.h"
#include "execute.h"
#include "iman.h"
#include "activities.h"
#include "signals.h"
#include "io_redirection.h"
#include "neonate.h"
#include "fg_bg.h"
#include "pastevents.h"

#define GREEN_COLOR "\x1b[32m"
#define RED_COLOR "\x1b[31m"
#define BLUE_COLOR "\x1b[34m"
#define RESET_COLOR "\x1b[0m"
#define BOLD_TEXT "\x1b[1m"
#define RESET_FORMAT "\x1b[0m"

extern int foreground_pid;
extern char* home;
extern char prompt_input[50];
extern int fg_running_flag;
extern ptrnode head;

#endif