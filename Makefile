# unity build
CC = gcc

# Compiler flags:
# -Wall                   : Enable most warning messages
# -Wextra                 : Enable extra warnings
# -Wpedantic              : Enforce strict ISO C compliance
# -Wconversion            : Warn on implicit type conversions that may change a value
# -Wsign-conversion       : Warn on implicit sign conversions
# -Wshadow                : Warn when a local variable shadows another
# -Wnull-dereference      : Warn if the compiler suspects a null-pointer deref
# -Wdouble-promotion      : Warn when float is promoted to double
# -Wformat=2              : Level-2 checks on printf/scanf format strings
# -std=c11                : Use the ISO C11 standard
# -fsanitize=address,undefined : Enable AddressSanitizer and UndefinedBehaviorSanitizer
CFLAGS =  -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Wshadow \
	-Wnull-dereference -Wdouble-promotion -Wformat=2 -std=c11 -fsanitize=address,undefined
SRC = src
TARGET = exec

all: $(TARGET)

$(TARGET): $(SRC)/main.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(TARGET)

