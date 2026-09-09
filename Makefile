CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Werror -Iinc
SRC = src/*.c tests/test_*.c
TARGET = bin/a.out

$(TARGET) : $(SRC)
	mkdir -p ./bin
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

.PHONY: test clean

test: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
