.PHONY: build test test-stack test-queue clean

# Locate test source files
TESTSRC = $(wildcard ../test*.c)
TEST = $(patsubst ../%.c,%,$(TESTSRC))

# Locate stack and queue tests
TEST_STACK = $(wildcard *Stack)
TEST_QUEUE = $(wildcard *Queue)

# Locate all non-test source files
SRC = $(filter-out $(TESTSRC), $(wildcard ../*.c))
EXEC = $(patsubst ../%.c,%,$(SRC))

# Locate header files
HEADERS = $(wildcard ../include/*.h)

CC = gcc
CC_FLAGS = -std=c99 -g -O0 -Wall -Wextra -pedantic
LDFLAGS = -lm

# Ensure executables are built in the same directory as the Makefile
build: $(EXEC) $(TEST)

# Compile main executables (excluding tests)
%: ../%.c $(HEADERS)
	@echo "Compiling $< -> $@"
	$(CC) $(CC_FLAGS) $< -o $@ $(LDFLAGS)

# Compile test executables
%: ../%.c $(HEADERS)
	@echo "Compiling test $< -> $@"
	$(CC) $(CC_FLAGS) $< -o $@ $(LDFLAGS)

# Run stack tests with Valgrind
test-stack: $(TEST_STACK)
	@for t in $(TEST_STACK); do \
		echo "Running stack test: $$t"; \
		valgrind --leak-check=full ./$$t; \
	done

# Run queue tests with Valgrind
test-queue: $(TEST_QUEUE)
	@for t in $(TEST_QUEUE); do \
		echo "Running queue test: $$t"; \
		valgrind --leak-check=full ./$$t; \
	done

clean:
	rm -f $(EXEC) $(TEST) $(TEST_STACK) $(TEST_QUEUE)
