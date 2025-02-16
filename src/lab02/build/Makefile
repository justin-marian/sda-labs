.PHONY: build test clean

# Locate source and test files in the parent directory
SRC = $(filter-out $(wildcard ../test*.c), $(wildcard ../*.c))
TESTSRC = $(wildcard ../test*.c)

# Extract executable names from source files
EXEC = $(patsubst ../%.c,%,$(SRC))
TEST = $(patsubst ../%.c,%,$(TESTSRC))

HEADERS = $(wildcard ../include/*.h)

CC = gcc
CC_FLAGS = -std=c99 -g -O0 -Wall -Wextra -pedantic

# Default target: build all executables
build: $(EXEC) $(TEST)

# Compile main executables (excluding tests)
$(EXEC): %: ../%.c $(HEADERS)
	$(CC) $(CC_FLAGS) $< -o $@

# Compile test executables separately
$(TEST): %: ../%.c $(HEADERS)
	$(CC) $(CC_FLAGS) $< -o $@

# Run tests with Valgrind
test: $(TEST)
	@for t in $(TEST); do \
		echo "Running test $$t"; \
		valgrind --leak-check=full ./$$t; \
	done

# Cleanup compiled files
clean:
	rm -f $(EXEC) $(TEST)
