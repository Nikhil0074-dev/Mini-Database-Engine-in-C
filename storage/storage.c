#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "storage.h"
#include "../utils/utils.h"

#define TABLE_FILE(table) ("data/" table ".tbl")

static FILE* open_table(const char* table_name, const char* mode) {
    char path[256];
    snprintf(path, sizeof(path), "%s/%s", "data", table_name);
    return fopen(path, "rb+");
}

int storage_create_table(const char* table_name) {
    FILE* file = fopen(TABLE_FILE(table_name), "wb");
    if (!file) return 0;

    TableHeader header = {0};
    strncpy(header.table_name, table_name, MAX_TABLE_NAME - 1);
    header.num_fields = 3;
    header.fields[0] = TYPE_INT; strncpy(header.field_names[0], "id", MAX_FIELD_NAME-1);
    header.fields[1] = TYPE_TEXT; strncpy(header.field_names[1], "name", MAX_FIELD_NAME-1);
    header.fields[2] = TYPE_INT; strncpy(header.field_names[2], "age", MAX_FIELD_NAME-1);
    header.num_rows = 0;

    fwrite(&header, sizeof(TableHeader), 1, file);
    fclose(file);
    return 1;
}

int storage_insert(const char* table_name, Record* rec) {
    FILE* file = fopen(TABLE_FILE(table_name), "rb+");
    if (!file) return 0;

    TableHeader header;
    fseek(file, 0, SEEK_SET);
    fread(&header, sizeof(TableHeader), 1, file);
    if (strncmp(header.table_name, table_name, MAX_TABLE_NAME) != 0) {
        fclose(file);
        return 0;
    }

    fseek(file, sizeof(TableHeader) + header.num_rows * RECORD_SIZE, SEEK_SET);
    fwrite(rec, RECORD_SIZE, 1, file);
    header.num_rows++;
    fseek(file, 0, SEEK_SET);
    fwrite(&header, sizeof(TableHeader), 1, file);
    fclose(file);
    return 1;
}

int storage_select_all(const char* table_name) {
    FILE* file = fopen(TABLE_FILE(table_name), "rb");
    if (!file) return 0;

    TableHeader header;
    fread(&header, sizeof(TableHeader), 1, file);
    Record rec;
    printf("Table: %s (%d rows)\n", header.table_name, header.num_rows);
    printf("id | name%40s | age\n", "");
    printf("---|------------------------------|----\n");

    fseek(file, sizeof(TableHeader), SEEK_SET);
    for (int i = 0; i < header.num_rows; i++) {
        fread(&rec, RECORD_SIZE, 1, file);
        rec.name[MAX_NAME_LEN-1] = '\0';  // Null-terminate
        printf("%-2d | %-24s | %d\n", rec.id, rec.name, rec.age);
    }
    fclose(file);
    return 1;
}

int storage_delete_where(const char* table_name, const char* condition) {
    // Simple ID-based delete for WHERE id = X
    int target_id = -1;
    if (strncmp(condition, "id=", 3) == 0) {
        target_id = str_to_int(condition + 3);
    }
    if (target_id == -1) return 0;

    FILE* file = fopen(TABLE_FILE(table_name), "rb+");
    if (!file) return 0;

    TableHeader header;
    fread(&header, sizeof(TableHeader), 1, file);
    int deleted = 0;
    Record rec, deleted_rec = {0};  // Tombstone: id=0

    for (int i = 0; i < header.num_rows; i++) {
        fseek(file, sizeof(TableHeader) + i * RECORD_SIZE, SEEK_SET);
        fread(&rec, RECORD_SIZE, 1, file);
        if (rec.id == target_id) {
            fseek(file, -RECORD_SIZE, SEEK_CUR);
            fwrite(&deleted_rec, RECORD_SIZE, 1, file);
            header.num_rows--;
            deleted = 1;
            // Simple: don't shift, just mark deleted and decrement count
        }
    }
    fseek(file, 0, SEEK_SET);
    fwrite(&header, sizeof(TableHeader), 1, file);
    fclose(file);
    return deleted;
}

int storage_update_where(const char* table_name, const char* set_field, int value, const char* condition) {
    int target_id = -1;
    if (strncmp(condition, "id=", 3) == 0) {
        target_id = str_to_int(condition + 3);
    }
    if (target_id == -1) return 0;

    FILE* file = fopen(TABLE_FILE(table_name), "rb+");
    if (!file) return 0;

    TableHeader header;
    fread(&header, sizeof(TableHeader), 1, file);
    Record rec;

    for (int i = 0; i < header.num_rows; i++) {
        fseek(file, sizeof(TableHeader) + i * RECORD_SIZE, SEEK_SET);
        fread(&rec, RECORD_SIZE, 1, file);
        if (rec.id == target_id) {
            fseek(file, -RECORD_SIZE, SEEK_CUR);
            if (strcmp(set_field, "age") == 0) {
                rec.age = value;
            }
            fwrite(&rec, RECORD_SIZE, 1, file);
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}
