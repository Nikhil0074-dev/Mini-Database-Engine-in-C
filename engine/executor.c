#include <stdio.h>
#include "executor.h"
#include "../storage/storage.h"
#include "../parser/parser.h"

int execute_command(const ParsedCommand* cmd) {
    switch (cmd->type) {
        case CMD_CREATE:
            if (storage_create_table(cmd->table_name)) {
                printf("Table '%s' created successfully.\n", cmd->table_name);
                return 1;
            }
            printf("Error creating table '%s'.\n", cmd->table_name);
            return 0;

        case CMD_INSERT:
            if (storage_insert(cmd->table_name, &cmd->insert_rec)) {
                printf("Record inserted into '%s'.\n", cmd->table_name);
                return 1;
            }
            printf("Error inserting into '%s'.\n", cmd->table_name);
            return 0;

        case CMD_SELECT:
            if (storage_select_all(cmd->table_name)) {
                return 1;
            }
            printf("Error selecting from '%s'.\n", cmd->table_name);
            return 0;

        case CMD_DELETE:
            if (storage_delete_where(cmd->table_name, cmd->where_cond)) {
                printf("Record deleted from '%s'.\n", cmd->table_name);
                return 1;
            }
            printf("No record deleted from '%s'.\n", cmd->table_name);
            return 0;

        case CMD_UPDATE:
            if (storage_update_where(cmd->table_name, cmd->set_field, cmd->set_value, cmd->where_cond)) {
                printf("Record updated in '%s'.\n", cmd->table_name);
                return 1;
            }
            printf("No record updated in '%s'.\n", cmd->table_name);
            return 0;

        default:
            printf("Unknown or unsupported command.\n");
            return 0;
    }
}
