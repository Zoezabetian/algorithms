#ifndef LIST_H_INCLUDE
#define LIST_H_INCLUDE

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct NodeObj {
  void* data;             // 
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
List newList(void); // Creates and returns a new empty List.
void freeList(List* pL); // Frees all heap memory associated with *pL, and sets
 // *pL to NULL.
// Access functions -----------------------------------------------------------
int length(List L); // Returns the number of elements in L.
int index(List L); // Returns index of cursor element if defined, -1 otherwise.
void* front(List L); // Returns front element of L. Pre: length()>0
void* back(List L); // Returns back element of L. Pre: length()>0
void* get(List L); // Returns cursor element of L. Pre: length()>0, index()>=0

                                        // Manipulation procedures ----------------------------------------------------
void clear(List L); // Resets L to its original empty state.

void set(List L, void* x); // Overwrites the cursor element’s data with x.
 // Pre: length()>0, index(()>=0

void moveFront(List L); // If L is non-empty, sets cursor under the front element,
 // otherwise does nothing.

void moveBack(List L); // If L is non-empty, sets cursor under the back element,
 // otherwise does nothing.

void movePrev(List L); // If cursor is defined and not at front, move cursor one
 // step toward the front of L; if cursor is defined and at
 // front, cursor becomes undefined; if cursor is undefined
 // do nothing

void moveNext(List L); // If cursor is defined and not at back, move cursor one
 // step toward the back of L; if cursor is defined and at
 // back, cursor becomes undefined; if cursor is undefined
 // do nothing
void prepend(List L, void* x); // Insert new element into L. If L is non-empty,
 // insertion takes place before front element.

void append(List L, void* x); // Insert new element into L. If L is non-empty,
 // insertion takes place after back element.

void insertBefore(List L, void* x); // Insert new element before cursor.
 // Pre: length()>0, index(()>=0

void insertAfter(List L, void* x); // Insert new element after cursor.
 // Pre: length()>0, index(()>=0

void deleteFront(List L); // Delete the front element. Pre: length()>0

void deleteBack(List L); // Delete the back element. Pre: length()>0

void delete(List L); // Delete cursor element, making cursor undefined.
 // Pre: length()>0, index(()>=0
// Other operations -----------------------------------------------------------



#endif // LIST_H_INCLude