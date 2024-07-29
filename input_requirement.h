#ifndef __INPUT_REQUIREMENT_
#define __INPUT_REQUIREMENT_

#include "headers.h"

void remove_whitespaces(char* input);
st_tokens tokenize(char* input);
char* symbol_str(char* input);

#endif