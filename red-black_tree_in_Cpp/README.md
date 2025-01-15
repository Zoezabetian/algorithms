# Red-Black Tree Algorithm in C++

## Description
This project developed an enhanced Dictionary Abstract Data Type (ADT) using a Red-Black Tree (RBT) as its underlying data structure to ensure efficient data operations and maintain balance. Initially built on a Binary Search Tree in C++ for managing unique keys with allowable duplicate values, this iteration incorporates RBT for improved performance, as outlined in the course materials and examples.

## Files Included

- `Order.cpp`: Top level client for the project that maps input file lines to dictionary keys for efficient data retrieval.
- `WordFrequency.cpp`: Second top-level client that reads each line of a file, parses the individual words on each line, converts each word to all lower case characters, then places it (as key) in a Dictionary. The number of times a given word is encountered (its frequency) will also be stored (as value) in the Dictionary
- `Dictionary.cpp`: Dictionary ADT implementation file.
- `Dictionary.h`: Dictionary header file (unchanged as provided).
- `DictionaryTest.cpp`: Test suite for the Red-Black Dictionary ADT.
- `Makefile`: Commands to compile the project.
- `README.md`: Project description and instructions.


## Build and Run Instructions

**To Build:**  
Run `make Order` or `make WordFrequency` in the terminal to compile either project.

**To Run:**  
Execute `./Order <input file> <output file>` or `./WordFrequency <input file> <output file>`
