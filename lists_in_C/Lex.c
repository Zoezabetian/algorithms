#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h" 

// extern int strcmp(const char* str1, const char* str2);

static void parseArgs(const int argc,
                      char* argv[],
                      char** inputFileName,
                      char** outputFileName) {
  if (argc != 3) {
    fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  *inputFileName = strdup(argv[1]);
  *outputFileName = strdup(argv[2]);
}

int main(int argc, char* argv[]) {
  char* inputFileName;
  char* outputFileName;

  parseArgs(argc, argv, &inputFileName, &outputFileName);

  FILE* inputFile = fopen(inputFileName, "r");
  if (inputFile == NULL) {
    perror("Error opening input file");
    exit(EXIT_FAILURE);
  }

  // Initialize a List L
  List L = newList();

  // Read the file quickly and get the number fof lines.
  int numberOfLines = 0;
  char line[1024];  // adjust 1024 to be large enough to hold any line in your
                    // file
  while (fgets(line, sizeof(line), inputFile) != NULL) {
    numberOfLines++;
  }

  int numberOfWords =  numberOfLines;  // We are to treat every line as a single word
  // Create an empty array to store words (initially NULL)
  char** wordArray;  // Adjust the size as needed
  wordArray = malloc(numberOfWords * sizeof(char*));
  if (wordArray == NULL) {
    perror("Memory allocation failed");
    exit(EXIT_FAILURE);
  }

  // Rewind to the beginning of the file
  rewind(inputFile);

  int lastWordIndex = 0;
  while (fgets(line, sizeof(line), inputFile) != NULL) {
    line[strcspn(line, "\n")] = 0;  // remove the \n character at the end
    // Dynamically allocate memory for the word and store it in the array

    char* word = strdup(line);  // duplicate line into word
    if (word == NULL) {
      perror("Memory allocation failed");
      exit(EXIT_FAILURE);
    }
    wordArray[lastWordIndex] = word;
    // insert each word into the List L in alphabetical order
    if (length(L) == 0) {        // if list empty
      append(L, lastWordIndex);      // append to "back" (even tho list is empty)
    } else {
      moveFront(L);                 // move cursor to front
      while (index(L) != -1) {  // as long as cursor defined:
        if (strcmp(word, wordArray[get(L)]) <
            0) {  // compare the current word with the word at the cursor
                  // position
          // The strcmp function returns a value less than zero if the first
          // string (word) is lexicographically less than the second string (the
          // word at the cursor position in wordArray).
          // In other words, it checks if word comes before the word at the
          // cursor position alphabetically.
          insertBefore(L,
                       lastWordIndex);  // insert current word before cursor
                                    // position if it comes first alphabetically
          break;
        }
        moveNext(L);  // move cursor
      }
      if (index(L) ==
          -1) {  // cursor becomes undefined (reaches the end of the list)
        append(L, lastWordIndex);  // appends word to end
      }
    }
    lastWordIndex++;  // increments and continues in wordarray
  }

  fclose(inputFile);

  // Open the output file for writing
  FILE* outputFile = fopen(outputFileName, "w");
  if (outputFile == NULL) {
    perror("Error opening output file");
    exit(EXIT_FAILURE);
  }

  // print sorted words to the output file
  moveFront(L);  // put cursor at front

  while (index(L) != -1) {  // index of cursor element not undefined
    fprintf(outputFile, "%s\n",
            wordArray[get(L)]);  // write word to output file
    moveNext(L);                 // proceed
  }

  // Close the output file
  fclose(outputFile);

  // Free dynamically allocated memory for words
  for (int i = 0; i < lastWordIndex; i++) {
    free(wordArray[i]);
  }
  free(wordArray);  // free the array itself
  // Free the List L
  freeList(&L);

  // Free inputFileName and outputFileName
  free(inputFileName);
  free(outputFileName);

  return 0;
}
