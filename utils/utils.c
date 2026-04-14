#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"

void trim(char* str) {
    char* end;
    while (isspace((unsigned char)*str)) str++;
    if (*str == 0) return;
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;
    end[1] = '\0';
}

char** tokenize(char* query, int* token_count) {
    trim(query);
    char* copy = strdup(query);
    char* token = strtok(copy, " ,();");
    int count = 0;
    char** tokens = malloc(MAX_QUERY_LEN / 2 * sizeof(char*));
    while (token) {
        trim(token);
        if (strlen(token) > 0) {
            tokens[count] = strdup(token);
            count++;
        }
        token = strtok(NULL, " ,();");
    }
    free(copy);
    *token_count = count;
    return tokens;
}

void free_tokens(char** tokens, int count) {
    for (int i = 0; i < count; i++) {
        free(tokens[i]);
    }
    free(tokens);
}

int str_to_int(const char* str) {
    return atoi(str);
}
