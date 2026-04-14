#ifndef PARSER_H
#define PARSER_H

#include "include/constants.h"
#include "../storage/storage.h"

typedef struct {
    CommandType type;
    char table_name[MAX_TABLE_NAME];
    Record insert_rec;
    char where_cond[32];  // e.g. "id=1"
    char set_field[32];   // e.g. "age"
    int set_value;
} ParsedCommand;

int parse_query(const char* query, ParsedCommand* cmd);

#endif
</xai:function_call)



<xai:function_call name="create_file">
<parameter name="absolute_path">C:/Users/dell/Desktop/mini_db_engine/parser/parser.c
