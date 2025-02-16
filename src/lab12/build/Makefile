all: lab_sd

lab_sd: graph.o ../main.c
	gcc ../main.c graph.o list.o stack.o queue.o -o lab_sd -g

graph.o: list.o stack.o queue.o ../include/graph.h ../graph.c
	gcc -c ../graph.c -g

list.o: ../list.c ../include/list.h
	gcc -c ../list.c -g

stack.o: ../stack.c ../include/stack.h
	gcc -c ../stack.c -g

queue.o: ../queue.c ../include/queue.h
	gcc -c ../queue.c -g

format:
	clang-format -i ../*.c ../include/*.h

valgrind: lab_sd
	valgrind --leak-check=full --show-leak-kinds=all ./lab_sd

clean:
	rm -f *.o *~ lab_sd rm *.dot *.png
