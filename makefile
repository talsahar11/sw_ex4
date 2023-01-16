CC = gcc
CFLAGS = -Wall -g
OBJECTS = graph.o algo.o
all: main.o lib_graph.a
	$(CC) $(CFLAGS) main.o graph.o lib_graph.a -o graph

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

lib_graph.a: graph.o algo.o
	ar -rcs lib_graph.a $(OBJECTS)

graph.o: graph.c graph.h
	$(CC) $(CFLAGS) -c graph.c

algo.o: algo.c algo.h
	$(CC) $(CFLAGS) -c algo.c


clean:
	rm -f *.o *.a graph