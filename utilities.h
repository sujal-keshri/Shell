#ifndef __UTILITIES_H_
#define __UTILITIES_H_

#include "headers.h"

ptrnode init_list();
ptrnode create_node(int pid, char* command);
void insert_process(ptrnode head, int pid, char* command, int r_s);
int check_p_status(int pid, char* command);
void search_and_delete(ptrnode head);
void free_node(ptrnode node);
void kill_all_processes(ptrnode head);

#endif