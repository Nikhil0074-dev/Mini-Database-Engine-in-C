#ifndef CONSTANTS_H
#define CONSTANTS_H

#define MAX_TABLE_NAME 32
#define MAX_FIELD_NAME 32
#define MAX_FIELDS 16
#define MAX_NAME_LEN 50
#define MAX_QUERY_LEN 256
#define RECORD_SIZE (sizeof(int) + MAX_NAME_LEN + sizeof(int))  // id(4) + name(50) + age(4) = 58 bytes
#define PAGE_SIZE 4096
#define DB_FILE "data/database.db"

typedef enum {
    TYPE_INT,
    TYPE_TEXT
} DataType;

typedef enum {
    CMD_CREATE,
    CMD_INSERT,
    CMD_SELECT,
    CMD_DELETE,
    CMD_UPDATE,
    CMD_UNKNOWN
} CommandType;

#endif
