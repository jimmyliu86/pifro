CC = c++ -Wall -std=c++0x -I ..

OBJS = graph.o

all: $(OBJS)
	$(CC) $(OBJS) main.cc -o dijkstra

graph.o: graph.h graph.cc heap.h
	$(CC) -c graph.cc

clean:
	rm *.o dijkstra *~ -f
