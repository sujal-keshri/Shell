#ifndef __NEONATE_H_
#define __NEONATE_H_

#include "headers.h"
#include <fcntl.h>

void die(const char *s);
void disableRawMode();
void enableRawMode();
void neonate_exe(char *s_delay);

#endif