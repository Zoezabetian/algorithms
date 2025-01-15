BASE_SOURCES   = Matrix.c List.c
BASE_OBJECTS   = Matrix.o List.o
HEADERS        = Matrix.h List.h
COMPILE        = gcc -std=c17 -Wall -c
LINK           = gcc -std=c17 -Wall -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full -s

Sparse: Sparse.o $(BASE_OBJECTS)
	$(LINK) Sparse Sparse.o $(BASE_OBJECTS)

MatrixTest: MatrixTest.o $(BASE_OBJECTS)
	$(LINK) MatrixTest MatrixTest.o $(BASE_OBJECTS)

ListTest: ListTest.o $(BASE_OBJECTS)
	$(LINK) ListTest ListTest.o List.o 

Sparse.o: Sparse.c $(HEADERS)
	$(COMPILE) Sparse.c

MatrixTest.o: MatrixTest.c $(HEADERS)
	$(COMPILE) MatrixTest.c

ListTest.o: ListTest.c $(HEADERS)
	$(COMPILE) ListTest.c

$(BASE_OBJECTS): $(BASE_SOURCES) $(HEADERS)
	$(COMPILE) $(BASE_SOURCES)

clean:
	$(REMOVE) Sparse MatrixTest ListTest Sparse.o MatrixTest.o ListTest.o $(BASE_OBJECTS)

checkSparse: Sparse
	$(MEMCHECK) Sparse in5 junk5

test: MatrixTest
	./MatrixTest

checkListTest: ListTest
	$(MEMCHECK) ListTest
