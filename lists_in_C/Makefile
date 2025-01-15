
CFLAGS = -std=c17 -Wall -Wno-incompatible-library-redeclaration

Lex : Lex.o List.o
	$(CC) $(CFLAGS) -o Lex Lex.o List.o

Lex.o : Lex.c List.h
	$(CC) $(CFLAGS) -c Lex.c

ListClient: ListClient.o List.o
	$(CC) $(CFLAGS) -o ListClient ListClient.o List.o

ListClient.o : ListClient.c List.h
	$(CC) $(CFLAGS) -c ListClient.c

List.o : List.c List.h
	$(CC) $(CFLAGS) -c List.c

clean :
	rm -f Lex ListClient Lex.o ListClient.o List.o ListTest ListTest.o

checkClient : 
	valgrind --leak-check=full ListClient

checkLex :
	valgrind --leak-check=full Lex in3 blah3

ListTest.o : ListTest.c List.h
	$(CC) $(CFLAGS) -c ListTest.c

ListTest: ListTest.o List.o
	$(CC) $(CFLAGS) -o ListTest ListTest.o List.o

test: ListTest
	./ListTest
