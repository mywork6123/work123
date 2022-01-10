CC=gcc
AR=ar
FLAGS=-Wall -g
LIBS=-lm
OBJECTS_MAIN=main.o
OBJECTS_GRAPH=graph.o

all: libgraph.a libgraph.so graph graphd

graph:	$(OBJECTS_MAIN) libgraph.a #static
	$(CC) $(FLAGS) -o graph $(OBJECTS_MAIN) libgraph.a $(LIBS)
graphd:	$(OBJECTS_MAIN) libgraph.so #dynamic
	$(CC) $(FLAGS) -o graphd $(OBJECTS_MAIN) ./libgraph.so $(LIBS)

libgraph.a:	$(OBJECTS_GRAPH)
	$(AR) -rcs libgraph.a $(OBJECTS_GRAPH)
libgraph.so:	$(OBJECTS_GRAPH)
	$(CC) $(FLAGS) -shared -o libgraph.so $(OBJECTS_GRAPH)
main.o:	main.c graph.h
	$(CC) $(FLAGS) -c main.c
graph.o: graph.c graph.h
	$(CC) $(FLAGS) -c graph.c $(LIBS)

.PHONY: clean all

clean:
	rm -f *.o *.a *.so graph graphd