#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/constants.h"
#include "parser/parser.h"
#include "engine/executor.h"

int main() {
    printf("MiniDB Engine v1.0 - Type 'exit' or 'quit' to quit.\n");
    printf("Supported: CREATE TABLE students (id INT, name TEXT, age INT); INSERT INTO students VALUES (1,'Nikhil',21); SELECT * FROM students; etc.\n\n");

    char query[MAX_QUERY_LEN];
    while (1) {
        printf("> ");
        if (!fgets(query, sizeof(query), stdin)) break;
        query[strcspn(query, "\n")] = 0;  // Remove newline

        if (strcasecmp(query, "exit") == 0 || strcasecmp(query, "quit") == 0) {
            break;
        }

        ParsedCommand cmd = {0};
        if (parse_query(query, &cmd)) {
            execute_command(&cmd);
        } else {
            printf("Parse error or unsupported query: %s\n", query);
        }
        printf("\n");
    }
    return 0;
}
</xai:function_call}




<xai:function_call name="create_file">
<parameter name="absolute_path">C:/Users/dell/Desktop/mini_db_engine/Makefile
