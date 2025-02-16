.PHONY: build run test clean format

CC = gcc
CFLAGS = -Wall -std=c99 -g -MMD -MP
BUILD_DIR = ../out
VPATH = ../include

# Ensure build directory exists
$(shell mkdir -p $(BUILD_DIR))

# Sources and Objects
SRC = ../Graph.c ../Util.c ../testGraph.c
OBJ = $(patsubst ../%.c, $(BUILD_DIR)/%.o, $(SRC))
DEP = $(OBJ:.o=.d)
EXEC = $(BUILD_DIR)/testGraph

# Default build target
build: $(EXEC)

# Linking Executable
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Compiling Source Files (objects placed in build/)
$(BUILD_DIR)/%.o: ../%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Ensure build directory exists
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Run the Executable
run: build
	$(BUILD_DIR)/$(EXEC)

# Memory Leak Test using Valgrind
test: build
	valgrind --leak-check=full --show-leak-kinds=all ./$(EXEC)

# Code Formatting
format:
	clang-format -i ../*.c ../include/*.h

# Clean Compiled Files
clean:
	rm -rf $(BUILD_DIR)
