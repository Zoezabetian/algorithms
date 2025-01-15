#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct NodeObj {
  int index;             // index into the array of strings
  struct NodeObj* next;  // this and next line needs the 'struct' because this
                         // struct is still in the processs of being defined.
  struct NodeObj* prev;
} NodeObj;

typedef NodeObj* Node;

typedef struct ListObj {
  Node front;
  Node back;
  Node cursor;
  int length;
  int index;
} ListObj;

typedef ListObj* List;

// List.h: This file should contain the declarations of functions and structures
// related to the List Abstract Data Type (ADT). It should define the List
// structure and specify the functions that will manipulate this data structure.

// Constructors-Destructors ---------------------------------------------------
List new(void); // Creates and returns a new empty List.
void free(List* pL); // Frees all heap memory associated with *pL, and sets
 // *pL to NULL.
// Access functions -----------------------------------------------------------
int length(List L); // Returns the number of elements in L.
int index(List L); // Returns index of cursor element if defined, -1 otherwise.
int front(List L); // Returns front element of L. Pre: length()>0
int back(List L); // Returns back element of L. Pre: length()>0
int get(List L); // Returns cursor element of L. Pre: length()>0, index()>=0
bool equals(List A, List B); // Returns true iff Lists A and B are in same
 // state, and returns false otherwise.
// Manipulation procedures ----------------------------------------------------
void clear(List L); // Resets L to its original empty state.
void set(List L, int x); // Overwrites the cursor element’s data with x.
 // Pre: length()>0, index()>=0
void toFront(List L); // If L is non-empty, sets cursor under the front element,
 // otherwise does nothing.
void toBack(List L); // If L is non-empty, sets cursor under the back element,
 // otherwise does nothing.
void previous(List L); // If cursor is defined and not at front, move cursor one
 // step toward the front of L; if cursor is defined and at
 // front, cursor becomes undefined; if cursor is undefined
 // do nothing
void next(List L); // If cursor is defined and not at back, move cursor one
 // step toward the back of L; if cursor is defined and at
 // back, cursor becomes undefined; if cursor is undefined
 // do nothing
void prepend(List L, int x); // Insert new element into L. If L is non-empty,
 // insertion takes place before front element.
void append(List L, int x); // Insert new element into L. If L is non-empty,
 // insertion takes place after back element.
void insertBefore(List L, int x); // Insert new element before cursor.
 // Pre: length()>0, index()>=0
void insertAfter(List L, int x); // Insert new element after cursor.
 // Pre: length()>0, index()>=0
void deleteFront(List L); // Delete the front element. Pre: length()>0
void deleteBack(List L); // Delete the back element. Pre: length()>0
void delete(List L); // Delete cursor element, making cursor undefined.
 // Pre: length()>0, index()>=0
// Other operations -----------------------------------------------------------
void printList(FILE* out, List L); // Prints to the file pointed to by out, a
 // string representation of L consisting
// of a space separated sequence of integers,
// with front on left.
List copyList(List L); // Returns a new List representing the same integer
 // sequence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L. The state
// of L is unchanged.