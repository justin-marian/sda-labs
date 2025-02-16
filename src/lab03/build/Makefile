.PHONY: build test test-problem clean

# Locate test and problem source files
TESTSRC = $(wildcard ../test*.c)
TEST = $(patsubst ../%.c,%,$(TESTSRC))

PROBSRC = ../problem.c
EXAMPLESRC = ../example.c
PROBLEMS = $(patsubst ../%.c,%,$(PROBSRC) $(EXAMPLESRC))

# Locate all non-test source files
SRC = $(filter-out $(TESTSRC) $(PROBSRC) $(EXAMPLESRC), $(wildcard ../*.c))
EXEC = $(patsubst ../%.c,%,$(SRC))

# Locate header files
HEADERS = $(wildcard ../include/*.h)

# Compiler settings
CC = gcc
CC_FLAGS = -std=c99 -g -O0 -Wall -Wextra -pedantic

# Default target: Build everything
build: $(EXEC) $(TEST) $(PROBLEMS)

# Compile main executables (excluding tests)
%: ../%.c $(HEADERS)
	@echo "Compiling $< -> $@"
	$(CC) $(CC_FLAGS) $< -o $@

# Compile problem-specific executables
%: ../%.c $(HEADERS)
	@echo "Compiling problem $< -> $@"
	$(CC) $(CC_FLAGS) $< -o $@

# Run all tests with Valgrind
test: $(TEST)
	@for t in $(TEST); do \
		echo "Running test $$t"; \
		valgrind --leak-check=full ./$$t; \
	done

# Run the specific problem test with Valgrind
test-problem: $(PROBLEMS)
	@echo "Running test-problems: $(PROBLEMS)"
	@valgrind --leak-check=full ./$(PROBLEMS)

# Cleanup compiled files
clean:
	rm -f $(EXEC) $(TEST) $(PROBLEMS)
