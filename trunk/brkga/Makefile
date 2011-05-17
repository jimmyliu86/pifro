OBJS = main.o graph.o instance.o dijkstra.o
CC = g++

all : $(OBJS)
	$(CC) $(OBJS) -o poc2

main : main.cc graph.h instance.h
	$(CC) -g -c main.cc

graph: graph.cc graph.h
	$(CC) -g -c graph.cc

instance: instance.cc instance.h graph.h macros.h
	$(CC) -g -c instance.cc

dijkstra: dijkstra.cc dijkstra.h graph.h macros.h constants.h
	$(CC) -g -c dijkstra.cc

solution: solution.cc solution.h graph.h
	$(CC) -g -c solution.cc

clean :
	rm -f *.o
