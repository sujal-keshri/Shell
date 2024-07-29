#ifndef __SIGNALS_H_
#define __SIGNALS_H_

#include "headers.h"

void send_signal(char* pid, char* sig_num);
void ctrl_c_func(int signal);

#endif