#include <stdio.h>
#include "../include/constants.h"
#include "../parser/parser.h"
#include "../engine/executor.h"

int main() {
    // Test cases
    char* tests[] = {
        "CREATE TABLE students (id INT, name TEXT, age INT)",
        "INSERT INTO students VALUES (1, 'Nikhil', 21)",
        "INSERT INTO students VALUES (2, 'Alice', 20)",
        "SELECT * FROM students",
        "UPDATE students SET age=22 WHERE id=1",
        "SELECT * FROM students",
        "DELETE FROM students WHERE id=2",
        "SELECT * FROM students"
    };
    int num_tests = sizeof(tests) / sizeof(tests[0]);

    for (int i = 0; i < num_tests; i++) {
        printf("\n--- Test %d: %s ---\n", i+1, tests[i]);
        ParsedCommand cmd = {0};
        if (parse_query(tests[i], &cmd)) {
            execute_command(&cmd);
        }
    }
    return 0;
}
</xai:function_call name="create_file"> 

No, wait for results first. Only one tool per message? No, parallel allowed.

But since previous were successful, continue.

Wait, this is the response after previous functions.

Now create README and tests.

Use multiple parallel. 
