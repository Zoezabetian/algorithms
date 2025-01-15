#define _POSIX_C_SOURCE 200809L  // adding for strdup func
#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"
#include <string.h>



static void parseArgs(const int argc,
                      char *argv[],
                      char **inputFileName,
                      char **outputFileName)
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    *inputFileName = strdup(argv[1]);
    *outputFileName = strdup(argv[2]);
}

int main(int argc, char *argv[])
{
    char *inputFileName;
    char *outputFileName;

    parseArgs(argc, argv, &inputFileName, &outputFileName);

    FILE *inputFile = fopen(inputFileName, "r");
    FILE *outputFile = fopen(outputFileName, "w");
    if (inputFile == NULL || outputFile == NULL)
    {
        perror("Error opening file");
        printf("Error opening file");
        fflush(stdout);
        exit(EXIT_FAILURE);
    }

    

    int n, a, b;
    if (fscanf(inputFile, "%d %d %d", &n, &a, &b) != 3) { //read first line
        fprintf(stderr, "Error: Invalid input format\n");
        fclose(inputFile);
        exit(EXIT_FAILURE);
    }

    fgetc(inputFile); // skip blank line


    // create row lists arrays for matrix A
    Matrix A = newMatrix(n);
    for (int i = 0; i < a; i++) {
        int row, col;
        double value;
        if (fscanf(inputFile, "%d %d %lf", &row, &col, &value) != 3) {
            fprintf(stderr, "Error: Invalid input format for matrix A\n");
            freeMatrix(&A);
            fclose(inputFile);
            exit(EXIT_FAILURE);
        }
        changeEntry(A, row, col, value);
    }
    
    fgetc(inputFile);

    // create row lists arrays for matrix B
    Matrix B = newMatrix(n);
    for (int i = 0; i < b; i++) {
        int row, col;
        double value;
        if (fscanf(inputFile, "%d %d %lf", &row, &col, &value) != 3) {
            fprintf(stderr, "Error: Invalid input format for matrix B\n");
            freeMatrix(&A);
            freeMatrix(&B);
            fclose(inputFile);
            exit(EXIT_FAILURE);
        }
        changeEntry(B, row, col, value);
    }

    // matrix operations
    Matrix scaledA = scalarMult(1.5, A);
    // printf("made scaledA\n");
    // fflush(stdout);
    Matrix sumAB = sum(A, B);
    // printf("made sumAB\n");
    // fflush(stdout);
    Matrix sumAA = sum(A, A);
    // printf("made sumAA\n");
    // fflush(stdout);
    Matrix diffBA = diff(B, A);
    // printf("made diffBA\n");
    // fflush(stdout);
    Matrix diffAA = diff(A, A);
    // printf("made diffAA\n");
    // fflush(stdout);
    Matrix transposeA = transpose(A);
    // printf("made transposeA\n");
    // fflush(stdout);
    Matrix productAB = product(A, B);
    // printf("made productAB\n");
    // fflush(stdout);
    Matrix productBB = product(B, B);
    // printf("made productBB\n");
    // fflush(stdout);
    

    fprintf(outputFile, "A has %d non-zero entries:\n", NNZ(A));
    printMatrix(outputFile, A);
    fprintf(outputFile, "\n");

    fprintf(outputFile, "B has %d non-zero entries:\n", NNZ(B));
    printMatrix(outputFile, B);
    fprintf(outputFile, "\n");

    fprintf(outputFile, "(1.5)*A =\n");
    printMatrix(outputFile, scaledA);
    fprintf(outputFile, "\n");

    fprintf(outputFile, "A+B =\n");
    printMatrix(outputFile, sumAB);
    fprintf(outputFile, "\n");

    fprintf(outputFile, "A+A =\n");
    printMatrix(outputFile, sumAA);
    fprintf(outputFile, "\n");

    fprintf(outputFile, "B-A =\n");
    printMatrix(outputFile, diffBA);
    fprintf(outputFile, "\n");

    fprintf(outputFile, "A-A =\n");
    printMatrix(outputFile, diffAA);
    fprintf(outputFile, "\n");

    fprintf(outputFile, "Transpose(A) =\n");
    printMatrix(outputFile, transposeA);
    fprintf(outputFile, "\n");

    fprintf(outputFile, "A*B =\n");
    printMatrix(outputFile, productAB);
    fprintf(outputFile, "\n");

    fprintf(outputFile, "B*B =\n");
    printMatrix(outputFile, productBB);

    fclose(inputFile);
    fclose(outputFile);

    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&scaledA);
    freeMatrix(&sumAB);
    freeMatrix(&sumAA);
    freeMatrix(&diffBA);
    freeMatrix(&diffAA);
    freeMatrix(&transposeA);
    freeMatrix(&productAB);
    freeMatrix(&productBB);
    
    free(inputFileName);
    free(outputFileName);

    return 0;
}
