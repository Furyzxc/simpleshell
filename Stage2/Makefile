# Serhii Ananiev, 39562 - Operating Systems Project 1
# CSC1021/simpleshell

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -g -std=c11   # -g enables debugging symbols

# Source directory
SRC_DIR = src

# Build directory for object files
OBJ_DIR = src/obj

# Output directory for executable
BIN_DIR = bin

# Source files
SRCS := $(shell find $(SRC_DIR) -name "*.c")

# Object files (mirror source structure in obj folder)
OBJS := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# Executable
TARGET = $(BIN_DIR)/simpleshell

# Default target
all: $(TARGET)

# Build executable
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

# Compile .c to .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Create directories if they don't exist
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Debug target (build with debug flags, ready for gdb)
debug: CFLAGS += -DDEBUG
debug: clean all

# Clean up
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)/simpleshell

# Phony targets
.PHONY: all clean debug
