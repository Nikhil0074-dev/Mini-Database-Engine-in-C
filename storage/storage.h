#ifndef STORAGE_H
#define STORAGE_H

#include "include/constants.h"

typedef struct {
    char table_name[MAX_TABLE_NAME];
    int num_fields;
    int num_rows;
    DataType fields[MAX_FIELDS];
    char field_names[MAX_FIELDS][MAX_FIELD_NAME];
} TableHeader;

typedef struct {
    int id;
    char name[MAX_NAME_LEN];
    int age;
} Record;  // Fixed for students table

int storage_create_table(const char* table_name);
int storage_insert(const char* table_name, Record* rec);
int storage_select_all(const char* table_name);
int storage_delete_where(const char* table_name, const char* condition);
int storage_update_where(const char* table_name, const char* set_field, int value, const char* condition);

#endif
