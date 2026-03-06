# Makefile for SimpleShell (auto-detects .c files)

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -g -std=c11

# Source files (find all .c files recursively)
SRCS := $(shell find . -name "*.c")

# Object files
OBJS := $(SRCS:.c=.o)

# Executable
TARGET = simpleshell

# Default target
all: $(TARGET)

# Build executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compile .c to .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets
.PHONY: all clean
