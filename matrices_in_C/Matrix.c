#include "Matrix.h"
#define EPSILON 1e-12
#include <math.h>



// Returns a reference to a new nXn Matrix object in the zero state.
Matrix newMatrix(int n)
{
    Matrix M = malloc(sizeof(MatrixObj));
    if (M == NULL)
    {
        fprintf(stderr, "Memory allocation failed for new Matrix\n");
        exit(EXIT_FAILURE);
    }

    M->rows = malloc(sizeof(List) * n); // allocate memory for row lists
    if (M->rows == NULL)
    {
        fprintf(stderr, "Memory allocation failed for rows in Matrix\n");
        exit(EXIT_FAILURE);
    }

    M->size = n;
    M->NNZ = 0; // initialize NNZ to 0

    for (int i = 0; i < n; i++)
    {
        M->rows[i] = newList(); // initialize each row as a new list to store Entry objects.
    }

    return M;
}

void addEntry(Matrix M, int row, int column, double value)
{
    if (value == 0)
        return; // only store the values that aren't 0.0

    Entry newEntry = malloc(sizeof(EntryObj));
    newEntry->column = column;
    newEntry->value = value;

    List rowList = M->rows[row];
    bool added = false;

    // iterate through the list to find the correct position based on column
    for (moveFront(rowList); index(rowList) >= 0; moveNext(rowList))
    {
        Entry currentEntry = (Entry)get(rowList); // typecast so that new element is an EntryObj
        if (currentEntry->column == column)
        {
            // Column matches, update value
            currentEntry->value = value;
            added = true;
            break;
        }
        else if (currentEntry->column > column)
        {
            // Found the insert position
            insertBefore(rowList, newEntry);
            added = true;
            break;
        }
    }
    if (!added)
    {
        // if not added, it means the new entry's column is greater than any existing entry's column
        append(rowList, newEntry);
    }
}


void freeMatrix(Matrix *pM)
{
    if (pM != NULL && *pM != NULL)
    {
        for (int i = 0; i < size(*pM); i++) {
            List rowList = (*pM)->rows[i];
            if (rowList != NULL) {
                moveFront(rowList);
                while (index(rowList) >= 0) {
                    Entry entry = (Entry)get(rowList); 
                    free(entry);
                    moveNext(rowList);
                }
                freeList(&rowList); 
                (*pM)->rows[i] = NULL; 
            }
        }
        free((*pM)->rows);
        free(*pM);
        *pM = NULL;
    }
}


// Return the size of square Matrix M.
int size(Matrix M)
{
    if (M == NULL)

    {
        fprintf(stderr, "Error: calling size() on NULL Matrix\n");
        return 0;
    }
    return M->size;
}

// Return the number of non-zero elements in M.
int NNZ(Matrix M)
{
    if (M == NULL)
    {
        fprintf(stderr, "Error: calling NNZ() on NULL Matrix\n");
        return 0;
    }
    return M->NNZ;
}

// Return true (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B)
{
    if (A == NULL || B == NULL)
    {
        fprintf(stderr, "Error: calling equals() on NULL Matrix\n");
        return false;
    }
    if (size(A) != size(B)) // must be the same size to be equal
    {
        return 0;
    }
    for (int i = 0; i < A->size; i++)
    {
        List rowListA = A->rows[i]; // accessing each row list of Matrix A
        List rowListB = B->rows[i]; // accessing each row list of Matrix B
        moveFront(rowListA);
        moveFront(rowListB);

        while (index(rowListA) >= 0 && index(rowListB) >= 0)
        {
            Entry entryA = get(rowListA); // each member of the row list is a pointer to an entryObj
            Entry entryB = get(rowListB);
            if (entryA->column != entryB->column || entryA->value != entryB->value)
            { // need to check both col and value fields
                return 0;
            }
            moveNext(rowListA);
            moveNext(rowListB);
        }
        if (index(rowListA) != -1 || index(rowListB) != -1)
        { // check for extra elements in either list
            return 0;
        }
    }
    return 1;
}

// Re-sets M to the zero Matrix state.
void makeZero(Matrix M)
{
    if (M == NULL)
    {
        fprintf(stderr, "Matrix Error: calling makeZero() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < M->size; i++)
    {
        List row = M->rows[i];
        moveFront(row);
        while (index(row) >= 0)
        {
            Entry E = (Entry)get(row);
            free(E); // frees Entry object
            moveNext(row);
        }
        clear(row); // clears list after freeing entries
    }

    M->NNZ = 0; // reset the non-zero count
}


// Changes the ith row, jth column of M to the value x.
// Pre: 1<=i<=size(M), 1<=j<=size(M)
void changeEntry(Matrix M, int i, int j, double x) {
    if (M == NULL) {
        fprintf(stderr, "Matrix Error: calling changeEntry() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
    if (i < 1 || i > M->size || j < 1 || j > M->size) {
        fprintf(stderr, "Matrix Error: changeEntry() called with invalid row or column indices\n");
        exit(EXIT_FAILURE);
    }

    List rowList = M->rows[i - 1]; // adjust index for 0-based array
    bool found = false;

    moveFront(rowList);
    while (index(rowList) >= 0) {
        Entry E = (Entry)get(rowList);
        if (E->column == j) { // if j exists, that means Mij is non-zero
            found = true;
            if (x == 0) {
                // case 2: Mij≠0 and x=0 (delete)
                free(E); // free entry
                delete(rowList); // remove from list
                M->NNZ--; // decrement num non-zero entries
            } else {
                // case 4: Mij≠0 and x≠0 (overwrite)
                E->value = x;
            }
            break;
        }
        if (E->column > j) break; // entries stored in sorted order by column index
        moveNext(rowList);
    }

    if (!found && x != 0) {
        // case 3: Mij=0 and x≠0 (insert new entry)
        Entry newEntry = malloc(sizeof(EntryObj));
        if (newEntry == NULL) {
            fprintf(stderr, "Memory allocation failed for new entry in changeEntry\n");
            exit(EXIT_FAILURE);
        }
        newEntry->column = j;
        newEntry->value = x;
        if (index(rowList) == -1) { // insert in sorted order
            append(rowList, newEntry); // append if we're at the end or list is empty
        } else {
            insertBefore(rowList, newEntry); // insert before the current position
        }
        M->NNZ++; // increment num non-zero entries
    }
}

// my helper func
Entry copyEntry(Entry E)
{
    if (E == NULL)
        return NULL; 

    Entry newEntry = malloc(sizeof(EntryObj));
    if (newEntry == NULL)
    {
        fprintf(stderr, "Error: Memory allocation for copyEntry failed\n");
        exit(EXIT_FAILURE);
    }
    newEntry->column = E->column;
    newEntry->value = E->value;
    return newEntry;
}


// Returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix A)
{
    if (A == NULL)
    {
        fprintf(stderr, "Error: calling copy() on NULL Matrix\n");
        return NULL;
    }
    Matrix copyA = newMatrix(A->size);
    copyA->NNZ = A->NNZ;
    copyA->size = A->size;
    for (int i = 0; i < size(A); i++)
    {
        List rowListA = A->rows[i];
        moveFront(rowListA);
        while (index(rowListA) >= 0)
        {
            Entry entryA = (Entry)get(rowListA);       // typecasting
            append(copyA->rows[i], copyEntry(entryA)); // helper func copyEntry
            moveNext(rowListA);
        }
    }
    return copyA;
}

// Returns a reference to a new Matrix object representing the transpose of A.
Matrix transpose(Matrix A)
{
    if (A == NULL)
    {
        fprintf(stderr, "Error: calling transpose() on NULL Matrix\n");
        return NULL;
    }
    Matrix AT = newMatrix(A->size);
    AT->NNZ = A->NNZ;
    AT->size = A->size;
    for (int i = 0; i < size(A); i++)
    {
        List rowListA = A->rows[i];
        moveFront(rowListA);
        while (index(rowListA) >= 0)
        {
            Entry entryA = (Entry)get(rowListA); // typecasting
            Entry transposeEntry = malloc(sizeof(EntryObj));
            transposeEntry->column = i + 1; // switching row with column so adjust for 1-based column indexing
            transposeEntry->value = entryA->value;
            append(AT->rows[entryA->column - 1], transposeEntry); // adjusting for 0-based indexing
            moveNext(rowListA);
        }
    }
    return AT;
}
// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A)
{
    if (A == NULL)
    {
        fprintf(stderr, "Error: calling scalarMult() on NULL Matrix\n");
        return NULL;
    }
    Matrix scaledA = newMatrix(A->size);
    scaledA->NNZ = A->NNZ;
    scaledA->size = A->size;
    for (int i = 0; i < size(A); i++)
    {
        List rowListA = A->rows[i];
        moveFront(rowListA);
        while (index(rowListA) >= 0)
        {
            Entry entryA = (Entry)get(rowListA); // typecasting
            Entry scaledEntry = malloc(sizeof(EntryObj));
            scaledEntry->column = entryA->column;
            scaledEntry->value = x * entryA->value;
            append(scaledA->rows[i], scaledEntry);
            moveNext(rowListA);
        }
    }
    return scaledA;
}
// computes the vector dot product of two matrix rows represented by Lists P and Q. Use this function
// together with function transpose() to help implement product(). Similar helper functions for the
// operations sum() and diff() will also be useful, and are highly recommended
double vectorDot(List P, List Q) {
    double sum = 0.0;
    moveFront(P);
    moveFront(Q);

    while (index(P) >= 0 && index(Q) >= 0) {
        Entry entryP = (Entry)get(P);
        Entry entryQ = (Entry)get(Q);

        if (entryP->column < entryQ->column) {
            moveNext(P);
        } else if (entryP->column > entryQ->column) {
            moveNext(Q);
        } else { // Columns match
            sum += entryP->value * entryQ->value; // Directly add product to sum
            moveNext(P);
            moveNext(Q);
        }
    }
    return sum;
}


// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)

Matrix sum(Matrix A, Matrix B) {
    if (A == NULL || B == NULL) {
        fprintf(stderr, "Error: calling sum() on NULL Matrix\n");
        return NULL;
    }
    if (size(A) != size(B)) {
        fprintf(stderr, "Error: calling sum() on Matrices with different sizes\n");
        return NULL;
    }
    
    Matrix copyA = copy(A);
    Matrix copyB = copy(B);
    Matrix C = newMatrix(size(A));

    for (int i = 0; i < copyA->size; i++) {
        List rowListA = copyA->rows[i];
        List rowListB = copyB->rows[i];
        List rowListC = C->rows[i];
        moveFront(rowListA);
        moveFront(rowListB);

        while (index(rowListA) >= 0 || index(rowListB) >= 0) {
            Entry entryA = (index(rowListA) >= 0) ? get(rowListA) : NULL;
            Entry entryB = (index(rowListB) >= 0) ? get(rowListB) : NULL;

            if (entryA != NULL && entryB != NULL && entryA->column == entryB->column) {
                double sumAandB = entryA->value + entryB->value;
                if (sumAandB != 0) {
                    Entry entryC = malloc(sizeof(EntryObj));
                    if (entryC == NULL) {
                        fprintf(stderr, "Error: Memory allocation for entryC failed\n");
                        exit(EXIT_FAILURE);
                    }
                    entryC->column = entryA->column;
                    entryC->value = sumAandB;
                    append(rowListC, entryC);
                    C->NNZ++; // increment NNZ for non-zero sum of A and B
                }
                moveNext(rowListA);
                moveNext(rowListB);
            } else if (entryA != NULL && (entryB == NULL || entryA->column < entryB->column)) {
                append(rowListC, copyEntry(entryA));
                C->NNZ++; // increment NNZ here for non-zero entryA
                moveNext(rowListA);
            } else if (entryB != NULL && (entryA == NULL || entryB->column < entryA->column)) {
                append(rowListC, copyEntry(entryB));
                C->NNZ++; // increment NNZ here for non-zero entryB
                moveNext(rowListB);
            }
        }
    }
    // free the copied matrices
    freeMatrix(&copyA);
    freeMatrix(&copyB);

    return C;
}



// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B) {
    if (A == NULL || B == NULL) {
        fprintf(stderr, "Error: calling diff() on NULL Matrix\n");
        return NULL;
    }
    if (size(A) != size(B)) {
        fprintf(stderr, "Error: calling diff() on Matrices with different sizes\n");
        return NULL;
    }

    Matrix C = newMatrix(size(A));
    for (int i = 0; i < A->size; i++) {
        List rowListA = A->rows[i];
        List rowListB = B->rows[i];
        List rowListC = C->rows[i];
        moveFront(rowListA);
        moveFront(rowListB);

        while (index(rowListA) >= 0 || index(rowListB) >= 0) {
            Entry entryA = (index(rowListA) >= 0) ? get(rowListA) : NULL;
            Entry entryB = (index(rowListB) >= 0) ? get(rowListB) : NULL;

            if (entryA != NULL && entryB != NULL && entryA->column == entryB->column) {
                double AminusB = entryA->value - entryB->value;
                if (AminusB != 0) {
                    Entry entryC = malloc(sizeof(EntryObj));
                    if (entryC == NULL) {
                        fprintf(stderr, "Memory allocation failed for entryC in diff\n");
                        exit(EXIT_FAILURE);
                    }
                    entryC->column = entryA->column;
                    entryC->value = AminusB;
                    append(rowListC, entryC); // append non-zero difference
                    C->NNZ++; // increment NNZ for non-zero result
                }
                moveNext(rowListA);
                moveNext(rowListB);

            } else if (entryA != NULL && (entryB == NULL || entryA->column < entryB->column)) {
                append(rowListC, copyEntry(entryA)); //append entry from A directly
                C->NNZ++; // increment NNZ for non-zero entry from A
                moveNext(rowListA);

            } else if (entryB != NULL && (entryA == NULL || entryB->column < entryA->column)) {
                // create a new entry with the negated value of entryB
                Entry entryC = malloc(sizeof(EntryObj));
                if (entryC == NULL) {
                    fprintf(stderr, "Memory allocation failed for entryC in diff\n");
                    exit(EXIT_FAILURE);
                }
                entryC->column = entryB->column;
                entryC->value = -entryB->value;
                append(rowListC, entryC); // append negated entry from B
                C->NNZ++; // increment NNZ for non-zero negated entry from B
                moveNext(rowListB);
            }
        }

        // handle remaining entries from A
        while (index(rowListA) >= 0) {
            append(rowListC, copyEntry(get(rowListA)));
            C->NNZ++; // increment NNZ for each remaining non-zero entry from A
            moveNext(rowListA);
        }

        // handle remaining entries from B with negated values
        while (index(rowListB) >= 0) {
            Entry entryB = get(rowListB);
            Entry entryC = malloc(sizeof(EntryObj));
            if (entryC == NULL) {
                fprintf(stderr, "Memory allocation failed for entryC in diff\n");
                exit(EXIT_FAILURE);
            }
            entryC->column = entryB->column;
            entryC->value = -entryB->value;
            append(rowListC, entryC); // append negated remaining entry from B
            C->NNZ++; // increment NNZ for each non-zero negated entry from B
            moveNext(rowListB);
        }
    }
    return C;
}

// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B)
{
    if (A == NULL || B == NULL)
    {
        fprintf(stderr, "Error: calling product() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
    if (size(A) != size(B))
    {
        fprintf(stderr, "Error: calling product() on Matrices with different sizes\n");
        exit(EXIT_FAILURE);
    }

    Matrix AB = newMatrix(size(A));
    Matrix BT = transpose(B);

    for (int i = 0; i < size(A); i++) { // iterate through each row of A
    List rowListA = A->rows[i];
    if (rowListA == NULL || length(rowListA) == 0) continue; // akip empty rows

    for (int j = 0; j < size(B); j++) { // iterate through each row of BT (each column of B)
        List rowListBT = BT->rows[j];
        if (rowListBT == NULL || length(rowListBT) == 0) continue; // skip empty columns

        double dot = vectorDot(rowListA, rowListBT);
        if (fabs(dot) > EPSILON) { // use a defined small epsilon to account for floating-point precision
            changeEntry(AB, i + 1, j + 1, dot); // adjusting for 1-based access for changeEntry()
        }
    }
}
    freeMatrix(&BT); // free the transposed matrix 
    return AB;
}

// Prints a string representation of Matrix M to filestream out. Zero rows
// are not printed. Each non-zero row is represented as one line consisting
// of the row number, followed by a colon, a space, then a space separated
// list of pairs "(col, val)" giving the column numbers and non-zero values
// in that row. The double val will be rounded to 1 decimal point.
void printMatrix(FILE *out, Matrix M)
{
    if (M == NULL)
    {
        fprintf(stderr, "Error: calling printMatrix() on NULL Matrix\n");
        return;
    }

    for (int i = 0; i < M->size; i++)
    {                              
        List rowList = M->rows[i]; 
        if (length(rowList) > 0) {
            moveFront(rowList);
            fprintf(out, "%d: ", i + 1); // print row number starting from 1

            while (index(rowList) >= 0)
            {
                Entry entry = (Entry)get(rowList);
                fprintf(out, "(%d, %.1f) ", entry->column, entry->value); // (col, val)
                moveNext(rowList);
            }
            fprintf(out, "\n");
        }
    }
}