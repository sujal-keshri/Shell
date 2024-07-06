#ifndef HEADERS_H_
#define HEADERS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#include "prompt.h"
#include "pwd.h"
#include "warp.h"
#include "peek.h"
#include "proclore.h"

#define GREEN_COLOR "\x1b[32m"
#define RED_COLOR "\x1b[31m"
#define BLUE_COLOR "\x1b[34m"
#define RESET_COLOR "\x1b[0m"
#define BOLD_TEXT "\x1b[1m"
#define RESET_FORMAT "\x1b[0m"

#endif