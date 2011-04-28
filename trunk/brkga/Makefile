OBJS = main.o graph.o instance.o
CC = g++

all : $(OBJS)
	$(CC) $(OBJS) -o poc2

main : main.cpp graph.h instance.h
	$(CC) -g -c main.cpp

graph: graph.cpp graph.h
	$(CC) -g -c graph.cpp

instance: instance.cpp instance.h graph.h
	$(CC) -g -c instance.cpp

clean :
	rm -f *.o
