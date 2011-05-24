OBJS = main.o graph.o instance.o dijkstra.o solution.o heuristic.o heap.o
CC = g++

all : $(OBJS)
	$(CC) $(OBJS) -o poc2

main : main.cc instance.h heuristic.h
	$(CC) -g -c main.cc

graph: graph.cc graph.h
	$(CC) -g -c graph.cc

instance: instance.cc instance.h graph.h macros.h
	$(CC) -g -c instance.cc

dijkstra: dijkstra.cc dijkstra.h graph.h macros.h constants.h heap.h
	$(CC) -g -c dijkstra.cc

solution: solution.cc solution.h graph.h
	$(CC) -g -c solution.cc

heuristic: heuristic.cc heuristic.h instance.h solution.h dijkstra.h
	$(CC) -g -c heuristic.cc

heap: heap.cc heap.h
	$(CC) -g -c heap.cc

tester: tester.cc tester.h instance.h heuristic.h
	$(CC) -g -c tester.cc

clean :
	rm -f *.o
