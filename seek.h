#ifndef __SEEK_H_
#define __SEEK_H_

#include "headers.h"

int search_dir_file(char* home, char*original_target_path, char *target_path, char *f_d_path, int flag, int found);
void seek(char *home, char* previous_directory, char *command);

#endif