CC = gcc
AR = ar
FLAGS= -Wall -Werror -g
all: graph 
graph: main.o graph.a
	$(CC) $(FLAGS) -o graph main.o graph.a
graph.a: algo.o
	$(AR) -rcs graph.a algo.o
main.o: main.c graph.h
	$(CC) $(FLAGS) -c main.c
algo.o: algo.c graph.h
	$(CC) $(FLAGS) -c algo.c

.PHONY: all clean

clean:
	rm -f *.o *.a graph