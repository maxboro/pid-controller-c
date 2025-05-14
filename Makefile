# unity build
CC = gcc
CFLAGS =  -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Wshadow \
	-Wnull-dereference -Wdouble-promotion -Wformat=2 -std=c11 -fsanitize=address,undefined
SRC = src
TARGET = exec

all: $(TARGET)

$(TARGET): $(SRC)/main.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(TARGET)

