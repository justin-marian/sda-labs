.PHONY: build clean

build: words

words: ../words.c
	gcc -g -o words ../words.c

format:
	clang-format -i ../words.c

valgrind: words
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./words

clean:
	rm -f words
