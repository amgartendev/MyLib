# Compiler
CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Werror -Iinc


# Sources
SRC = $(wildcard src/*.c)
TEST_SRC = $(wildcard tests/test_*.c)
HEADERS = $(wildcard inc/mylib/*.h tests/*.h)


# Objects
OBJ = $(patsubst src/%.c,obj/%.o,$(SRC))
TEST_OBJ = $(patsubst tests/%.c,obj/%.o,$(TEST_SRC))


# Platform
ifeq ($(OS),Windows_NT)
	SHELL := cmd.exe

	TARGET = bin\tests.exe
	EXEC = .\$(TARGET)

	MKDIR_OBJ = if not exist obj mkdir obj
	MKDIR_BIN = if not exist bin mkdir bin

	CLEAN_OBJ = if exist obj\*.o del obj\*.o
	CLEAN_BIN = if exist $(TARGET) del $(TARGET)
else
	TARGET = bin/tests
	EXEC = ./$(TARGET)

	MKDIR_OBJ = mkdir -p obj
	MKDIR_BIN = mkdir -p bin

	CLEAN_OBJ = rm -f obj/*.o
	CLEAN_BIN = rm -f $(TARGET)
endif


# Build
$(TARGET): $(OBJ) $(TEST_OBJ)
	$(MKDIR_BIN)
	$(CC) $(CFLAGS) $(OBJ) $(TEST_OBJ) -o $(TARGET)


obj/%.o: src/%.c $(HEADERS)
	$(MKDIR_OBJ)
	$(CC) $(CFLAGS) -c $< -o $@


obj/%.o: tests/%.c $(HEADERS)
	$(MKDIR_OBJ)
	$(CC) $(CFLAGS) -c $< -o $@


# Commands
.PHONY: test clean


test: $(TARGET)
	$(EXEC)


clean:
	$(CLEAN_OBJ)
	$(CLEAN_BIN)