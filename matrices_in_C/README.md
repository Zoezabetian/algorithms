# Matrices Operations in C

## Description

This C program constructs and utilizes an efficient matrix operation calculator designed to leverage the sparseness of matrices it operates on. The core objective is to enable fast computations for large matrices by taking advantage of this sparseness, thus avoiding the computational overhead associated with dense matrix operations. Significant modifications have been made to the List functions to accommodate generic pointers, allowing for greater flexibility and reusability of the List ADT. 

## Files Included

- `List.h`: Header file with declarations for the List ADT. It defines the interface for a doubly linked list that is used to store rows of the sparse matrix, where each node in the list represents a non-zero entry in the matrix.
- `List.c`: Source file that implements the List ADT functions declared in `List.h`. It includes the logic for creating, manipulating, and destroying the List ADT, including operations such as insertions, deletions, and traversals which are essential for managing the sparse matrix's non-zero entries.
- `Matrix.h`: A header file that declares the Matrix ADT, designed to efficiently represent a sparse matrix. This file outlines the structure of the Matrix ADT and the public functions available for performing operations such as matrix addition, subtraction, and multiplication.
- `Matrix.c`: Implements the Matrix ADT functions declared in Matrix.h. This source file contains the logic for matrix operations that take advantage of the sparse nature of the matrices to optimize performance. Operations are implemented in a way that minimizes computational complexity by directly accessing non-zero elements.
- `Sparse.c`: The main program that utilizes the Matrix and List ADTs to read matrix data from input files, perform operations on them, and output the results. It serves as the user interface for executing matrix operations, handling input/output, and orchestrating the flow of the program.
- `Makefile`: A makefile with instructions for compiling the project.

## Build and Run Instructions

**To Build:**  
Run the command: `make`

**To Run:**  
Execute the program: `./Sparse <input file> <output file>`
