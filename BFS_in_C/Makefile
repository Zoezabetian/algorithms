BASE_SOURCES   = Graph.c List.c
BASE_OBJECTS   = Graph.o List.o
HEADERS        = Graph.h List.h
COMPILE        = gcc -std=c17 -Wall -c
LINK           = gcc -std=c17 -Wall -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full -s

shortestPath : shortestPath.o $(BASE_OBJECTS)
	$(LINK) shortestPath shortestPath.o $(BASE_OBJECTS)

GraphClient : GraphClient.o $(BASE_OBJECTS)
	$(LINK) GraphClient GraphClient.o $(BASE_OBJECTS)

shortestPath.o : shortestPath.c $(HEADERS)
	$(COMPILE) shortestPath.c

GraphClient.o : GraphClient.c $(HEADERS)
	$(COMPILE) GraphClient.c

$(BASE_OBJECTS) : $(BASE_SOURCES) $(HEADERS)
	$(COMPILE) $(BASE_SOURCES)

clean :
	$(REMOVE) shortestPath GraphClient shortestPath.o GraphClient.o $(BASE_OBJECTS)

checkFind : shortestPath
	$(MEMCHECK) shortestPath in7 junk7

checkClient : GraphClient
	$(MEMCHECK) GraphClient

	# Add a new target to compile the test file
GraphTest.o : GraphTest.c Graph.h List.h 
	gcc -std=c17 -Wall -c GraphTest.c

# Add a new target to link the test file and create an executable
GraphTest: GraphTest.o Graph.o List.o 
	gcc -std=c17 -Wall -o GraphTest GraphTest.o Graph.o List.o 

# Add a new target to run the tests
test: GraphTest
	./GraphTest