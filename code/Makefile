OBJS = main.o graph.o instance.o
CC = g++

all : $(OBJS)
	$(CC) -g $(OBJS) -o poc2 -lm

main : main.cc instance.h
	$(CC) -g -c main.cc

graph: graph.cc graph.h
	$(CC) -g -c graph.cc

instance: instance.cc instance.h graph.h macros.h
	$(CC) -g -c instance.cc

clean :
	rm -f *.o
