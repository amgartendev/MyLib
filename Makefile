CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Werror -Iinc
SRC = src/*.c tests/test_*.c

ifeq ($(OS), Windows_NT)
	TARGET = bin\tests.exe
	MKDIR = if not exist bin mkdir bin
	EXEC = .\$(TARGET)
	CLEAN = if exist $(TARGET) del $(TARGET)
else
	TARGET = bin/tests
	MKDIR = mkdir -p bin
	EXEC = ./$(TARGET)
	CLEAN = rm -f $(TARGET)
endif

$(TARGET) : $(SRC)
	$(MKDIR)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

.PHONY: test clean

test: $(TARGET)
	$(EXEC)

clean:
	$(CLEAN)
