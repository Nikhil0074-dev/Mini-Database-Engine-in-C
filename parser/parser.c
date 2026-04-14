#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parser.h"
#include "../utils/utils.h"

int parse_query(const char* query, ParsedCommand* cmd) {
    int token_count;
    char** tokens = tokenize((char*)query, &token_count);
    if (token_count < 2) {
        free_tokens(tokens, token_count);
        return 0;
    }

    // Determine command type
    if (strcasecmp(tokens[0], "CREATE") == 0 && strcasecmp(tokens[1], "TABLE") == 0) {
        cmd->type = CMD_CREATE;
        strncpy(cmd->table_name, tokens[2], MAX_TABLE_NAME - 1);
    } else if (strcasecmp(tokens[0], "INSERT") == 0) {
        cmd->type = CMD_INSERT;
        strncpy(cmd->table_name, tokens[2], MAX_TABLE_NAME - 1);
        cmd->insert_rec.id = str_to_int(tokens[4]);  // Assume VALUES (1, 'name', 21)
        strncpy(cmd->insert_rec.name, tokens[6], MAX_NAME_LEN - 1);
        cmd->insert_rec.age = str_to_int(tokens[8]);
    } else if (strcasecmp(tokens[0], "SELECT") == 0) {
        cmd->type = CMD_SELECT;
        strncpy(cmd->table_name, tokens[3], MAX_TABLE_NAME - 1);  // SELECT * FROM table
    } else if (strcasecmp(tokens[0], "DELETE") == 0) {
        cmd->type = CMD_DELETE;
        strncpy(cmd->table_name, tokens[2], MAX_TABLE_NAME - 1);
        strncpy(cmd->where_cond, tokens[4], 31);  // WHERE id=1
    } else if (strcasecmp(tokens[0], "UPDATE") == 0) {
        cmd->type = CMD_UPDATE;
        strncpy(cmd->table_name, tokens[1], MAX_TABLE_NAME - 1);
        strncpy(cmd->set_field, tokens[3], 31);  // SET age = 
        cmd->set_value = str_to_int(tokens[5]);
        strncpy(cmd->where_cond, tokens[8], 31);  // WHERE id =
    } else {
        cmd->type = CMD_UNKNOWN;
    }

    free_tokens(tokens, token_count);
    return (cmd->type != CMD_UNKNOWN);
}
