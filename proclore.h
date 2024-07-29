#ifndef __PROCLORE_H_
#define __PROCLORE_H_

#include "headers.h"

void print_executable_path(char* home, int pid);
int check_foreground_background(int pid);
void proclore(char* home, char* command, int p);

#endif