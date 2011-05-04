OBJS = main.o graph.o instance.o
CC = g++

all : $(OBJS)
	$(CC) $(OBJS) -o poc2

main : main.cc graph.h instance.h
	$(CC) -g -c main.cc

graph: graph.cc graph.h
	$(CC) -g -c graph.cc

instance: instance.cc instance.h graph.h macros.h
	$(CC) -g -c instance.cc

clean :
	rm -f *.o
