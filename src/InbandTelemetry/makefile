EXEC = int

CC = g++

CFLAGS = -c -Wall

$(EXEC): main.o AdjacencyList.o AdjacentNode.o Edge.o EdgeLength.o Graph.o LinkedList.o Node.o NodePath.o Stack.o
	$(CC) -o $(EXEC) main.o  AdjacencyList.o AdjacentNode.o Edge.o EdgeLength.o Graph.o LinkedList.o Node.o NodePath.o Stack.o

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp


AdjacencList.o : AdjacencyList.cpp AdjacencyList.h LinkedList.hfl
	$(CC) $(CFLAGS) AdjacencyList.cpp

AdjacentNode.o : AdjacentNode.cpp AdjacentNode.h
	$(CC) $(CFLAGS) AdjacentNode.cpp

Edge.o : Edge.cpp Edge.h
	$(CC) $(CFLAGS) Edge.cpp

EdgeLength.o : EdgeLength.cpp EdgeLength.h
	$(CC) $(CFLAGS) EdgeLength.cpp
 
Graph.o : Graph.cpp Graph.h LinkedList.h EdgeLength.h AdjacencyList.h NodePath.h Stack.h
	$(CC) $(CFLAGS) Graph.cpp

LinkedList.o : LinkedList.cpp LinkedList.h Node.h
	$(CC) $(CFLAGS) LinkedList.cpp

Node.o : Node.cpp Node.h
	$(CC) $(CFLAGS) Node.cpp

NodePath.o : NodePath.cpp NodePath.h
	$(CC) $(CFLAGS) NodePath.cpp

Stack.o : Stack.cpp Stack.h LinkedList.h
	$(CC) $(CFLAGS) Stack.cpp

clean :
	rm *.o
