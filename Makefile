CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Iinclude
TARGET = mini_db
SRCS = main.c utils/utils.c storage/storage.c parser/parser.c engine/executor.c
OBJS = $(SRCS:.c=.o)

.PHONY: all clean test

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

test: $(TARGET)
	./$(TARGET)

# Test binary
test_queries: tests/test_queries.c $(TARGET)
	$(CC) $(CFLAGS) tests/test_queries.c -o tests/test_mini_db_test $(OBJS)

