POC2_OBJS = poc2.o graph.o instance.o
POC3_OBJS = poc3.o dijkstra.o graph2.o traffic_hand.o
CC = g++

all: $(POC2_OBJS) $(POC3_OBJS)
	$(CC) -g $(POC2_OBJS) -o poc2 -lm
	$(CC) -g $(POC3_OBJS) -o poc3 -lm

poc2: poc2.cc instance.h
	$(CC) -g -c poc2.cc

poc3: poc3.cc
	$(CC) -g -c poc3.cc

graph: graph.cc graph.h
	$(CC) -g -c graph.cc

instance: instance.cc instance.h graph.h macros.h
	$(CC) -g -c instance.cc

graph2: graph2.cc
	$(CC) -g -c graph2.cc

dijkstra: dijkstra.cc
	$(CC) -g -c dijkstra.cc

traffic_hand: traffic_hand.cc
	$(CC) -g -c traffic_hand.cc

clean:
	rm -f *.o poc2 poc3 *~
