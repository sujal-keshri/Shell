#ifndef __PASTEVENTS_H_
#define __PASTEVENTS_H_

#include "headers.h"

char* get_nth_command(int n);
void save_history(char *command);
void display_history();
void delete_entries();

#endif