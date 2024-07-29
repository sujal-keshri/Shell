#ifndef __PEEK_H_
#define __PEEK_H_

#include "headers.h"
#include <pwd.h>
#include <grp.h>
#include <time.h>

typedef struct dirent* entry;
typedef entry* list;

// void peek();
// list give_list(char* path);
// struct stat give_stat(char* entry_path);
// int entry_type(struct stat entry_info);

char *give_entry_path(char *dir_path, char *entry_name);
list give_list(char *dir_path);
struct stat give_stat(char *entry_path);
int entry_type(struct stat entry_info);
char *permission(char *entry_path);
void print_entry_name(char* entry, char* entry_path);
void print_entry_info(char* entry, char* entry_path);
void print_dir(char *home, char *previous_directory, char *command, int flag);
void print_l_dir(char *home, char *previous_directory, char *command, int flag);
void peek(char *home, char *previous_directory, char *command);

#endif