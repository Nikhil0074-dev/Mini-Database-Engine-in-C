# Mini Database Engine in C 

A lightweight SQL-like database engine built from scratch in C. Supports basic CRUD operations with WHERE clause.

## Features 
- `CREATE TABLE students (id INT, name TEXT, age INT);`
- `INSERT INTO students VALUES (1, 'Nikhil', 22);`
- `SELECT * FROM students;`
- `DELETE FROM students WHERE id=1;`
- `UPDATE students SET age=22 WHERE id=1;`

Data stored in `data/students.tbl` (binary format).

## Quick Start 

```bash
cd mini_db_engine
make
./mini_db
```

**Example session:**
```
> CREATE TABLE students (id INT, name TEXT, age INT);
Table 'students' created successfully.

> INSERT INTO students VALUES (1, 'Nikhil', 22);
Record inserted into 'students'.

> SELECT * FROM students;
Table: students (1 rows)
id | name                       | age
---|----------------------------|----
 1 | Nikhil                     | 22

> UPDATE students SET age=22 WHERE id=1;
Record updated in 'students'.

> SELECT * FROM students;
 1 | Nikhil                     | 22

> DELETE FROM students WHERE id=1;
Record deleted from 'students'.
```

## Architecture 
```
CLI (main.c) → Parser → Executor → Storage → data/*.tbl
```

## Build & Test
```bash
make clean all
make test  # Runs mini_db REPL
# Or
make test_queries && ./tests/test_mini_db_test
```

## Limitations
- Fixed schema (3 fields: id INT, name TEXT(50), age INT).
- One table per .tbl file.
- Simple WHERE (only `id=X`).
- No quoting for names with spaces/apostrophes.
- No error recovery/full validation.

## Files
- `main.c`: REPL
- `parser/`: Tokenize & parse SQL-like queries
- `engine/`: Execute commands
- `storage/`: Binary file I/O
- `utils/`: Helpers
