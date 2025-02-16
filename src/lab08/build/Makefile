.PHONY: build test clean

# Collect test source files
TESTSRC = $(wildcard ../Test*.c)
TEST = $(patsubst ../%.c,%,$(TESTSRC))

# Collect all C source files excluding test files
SRC = $(filter-out $(TESTSRC), $(wildcard ../*.c))
EXEC = $(patsubst ../%.c,%,$(SRC))

HEADERS = $(wildcard ../include/*.h)

CC = gcc
CC_FLAGS = -std=c9x -g -O0
LD_FLAGS = -lm

# Build executables and tests in the current directory
build: $(EXEC) $(TEST)

test: $(TEST)
	valgrind --leak-check=full ./$(notdir $(TEST))

# Compile normal executables
$(EXEC): %: ../%.c $(HEADERS)
	$(CC) $(CC_FLAGS) $< -o $@ $(LD_FLAGS)

# Compile test executables
$(TEST): %: ../%.c $(HEADERS)
	$(CC) $(CC_FLAGS) $< -o $@ $(LD_FLAGS)

clean:
	rm -f $(EXEC) $(TEST)
