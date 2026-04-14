#ifndef UTILS_H
#define UTILS_H

#include "include/constants.h"

void trim(char* str);
char** tokenize(char* query, int* token_count);
void free_tokens(char** tokens, int count);
int str_to_int(const char* str);

#endif
