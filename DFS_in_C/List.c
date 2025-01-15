#include "List.h"
#include <stdlib.h>

// Creates and returns a new empty List.
List newList(void)
{
    // use L since the header file seems to like it.
    List L = malloc(sizeof(ListObj));
    L->front = NULL;
    L->back = NULL;
    L->cursor = NULL;
    L->length = 0;
    L->index = -1; // empty so index -1
    return L;
}

// Frees all heap memory associated with *pL, and sets *pL to NULL.
void freeList(List *pL)
{
    if (pL != NULL && *pL != NULL)
    {
        while (length(*pL) > 0)
        {
            deleteFront(*pL);
        }
        free(*pL);
        *pL = NULL;
    }
}

// Returns the number of elments in L.
int length(List L)
{
    if (L == NULL)
    {
        fprintf(stderr, "Error: calling length() on NULL List\n");
        return 0;
    }
    return L->length;
}

// Returns index of cursor element if defined, -1 otherwise.
int index(List L)
{
    if (L == NULL)
    {
        fprintf(stderr, "Error: calling index(() on NULL List\n");
        return -1;
    }
    return L->index;
}

// Returns front element of L. Pre: length()>0
int front(List L)
{
    if (L == NULL)
    {
        fprintf(stderr, "Error: calling front() on NULL List\n");
        return -1;
    }
    if (length(L) <= 0)
    {
        fprintf(stderr, "Error: calling front() on empty List\n");
        return -1;
    }
    return L->front->data; // dereferences the list item at the front (index 0)
}

// Returns back element of L. Pre: length()>0
int back(List L)
{
    if (L == NULL)
    {
        fprintf(stderr, "Error: calling back() on NULL List\n");
        return -1;
    }
    if (length(L) <= 0)
    {
        fprintf(stderr, "Error: calling back() on empty List\n");
        return -1;
    }
    return L->back->data; // dereferences the list item at the back of list
}

// Returns cursor element of L. Pre: length()>0, index(()>=0
int get(List L)
{
    if (L == NULL)
    {
        fprintf(stderr, "Error: calling get() on NULL List\n");
        return -1;
    }
    if (length(L) <= 0)
    {
        fprintf(stderr, "Error: calling get() on empty List\n");
        return -1;
    }
    if (index(L) < 0)
    {
        fprintf(stderr, "Error: calling get() on undefined cursor\n");
        return -1;
    }
    return L->cursor->data; // dereferences the cursor position to access the index field of the node at that position
}

// Returns true (1) iff Lists A and B are in same state, and returns false
// otherwise.
bool equals(List A, List B)
{
    if (A == NULL || B == NULL)
    {
        fprintf(stderr, "Error: calling equals() on NULL List\n");
        return false;
    }
    if (length(A) != length(B))
    {
        return false;
    }
    Node a = A->front;
    Node b = B->front;
    while (a != NULL && b != NULL)
    {
        if (a->data != b->data)
        {
            // elements are not equal
            return false;
        }
        a = a->next; // advances both a and b to their respective next nodes
        b = b->next;
    }
    return true; // a->next and b->next become NULL at end of list, so if they reach NULL then they are equal
}

// Manipulation procedures ----------------------------------------------------
// Resets L to its original empty state.
void clear(List L)
{
    if (L == NULL)
    {
        fprintf(stderr, "Error: calling clear() on NULL List\n");
        return;
    }
    while (length(L) > 0)
    { // ensures that all nodes in the list are removed
        deleteFront(L);
    }
    L->front = NULL; // no front or back elements in the empty list
    L->back = NULL;
    L->cursor = NULL; // make cursor undefined
    L->length = 0;
    L->index = -1;
}

// Overwrites the cursor element’s data with x.
// Pre: length()>0, index(()>=0
void set(List L, int x)
{
    if (L == NULL)
    {
        fprintf(stderr, "Error: calling set() on NULL List\n");
        return;
    }
    if (length(L) <= 0)
    {
        fprintf(stderr, "Error: calling set() on empty List\n");
        return;
    }
    L->front->data = x; // set the value of the cursor element's index field (data) to the int value x
}

// If L is non-empty, sets cursor under the front element,
// otherwise does nothing.
void moveFront(List L)
{
    if (L == NULL)
    {
        fprintf(stderr, "Error: calling moveFront() on NULL List\n");
        return;
    }
    if (length(L) <= 0)
    {
        // fprintf(stderr, "Error: calling moveFront() on empty List\n");
        return;
    }
    L->cursor = L->front; // sets cursor element to front of list
    L->index = 0;         // which is index 0
}

// If L is non-empty, sets cursor under the back element,
// otherwise does nothing.
void moveBack(List L)
{
    if (L == NULL)
    {
        fprintf(stderr, "Error: calling moveBack() on NULL List\n");
        return;
    }
    if (length(L) <= 0)
    {
        fprintf(stderr, "Error: calling moveBack() on empty List\n");
        return;
    }
    L->cursor = L->back;      // sets cursor to last element of list
    L->index = length(L) - 1; // which is at the index of length-1
}

// If cursor is defined and not at front, move cursor
// one step toward the front of L; if cursor is defined
// and at front, cursor becomes undefined; if cursor is
// undefined do nothing
void movePrev(List L)
{
    if (L == NULL)
    {
        fprintf(stderr, "Error: calling movePrev() on NULL List\n");
        return;
    }
    if (L->cursor == NULL)
    {
        return;
    }
    if (L->cursor == L->front)
    {                     // if cursor is at the front
        L->cursor = NULL; // movePrev would set cursor to null and index to -1 (undefined)
        L->index = -1;
    }
    else
    {
        L->cursor = L->cursor->prev; // dereferences L->cursor (by accessing the prev pointer
                                     //  of the node it points to) and then updates L->cursor to point
                                     //  to the previous node in the list
        L->index--;                  // updates new index position of the cursor after moving it (decrements index by 1)
    }
};

// If cursor is defined and not at back, move cursor one
// step toward the back of L; if cursor is defined and at
// back, cursor becomes undefined; if cursor is undefined
// do nothing
void moveNext(List L)
{
    if (L == NULL)
    {
        fprintf(stderr, "Error: calling moveNext() on NULL List\n");
        return;
    }
    if (L->cursor == NULL)
    {
        return;
    }
    if (L->cursor == L->back)
    {                     // if cursor is at the back
        L->cursor = NULL; // moveNext would set cursor to null and index to -1 (undefined)
        L->index = -1;
    }
    else
    {
        L->cursor = L->cursor->next; // dereferences L->cursor and updates cursor position to ->next
        L->index++;                  // updates index by incrementing by 1
    }
}

// Insert new element into L. If L is non-empty, insertion takes place before front element.
void prepend(List L, int x)
{
    if (L == NULL)
    {
        fprintf(stderr, "Error: calling prepend() on NULL List\n");
        return;
    }
    Node n = malloc(sizeof(NodeObj)); // allocates memory for a new node n using malloc
    n->data = x;                      // index of node (value stored) is x
    n->next = L->front;               // the inserted node's next pointer will point to the list's current front (which now becomes the second element in the list)
    n->prev = NULL;                   // the node's prev pointer will be null as the node is the first element of the list
    if (L->front != NULL)
    {
        L->front->prev = n; // this attaches a prev pointer to the list's current front (which is now the second element) so that it points to n (which is now the first element)
    }
    L->front = n; // now updates list so that front pointer points to n
    if (L->back == NULL)
    {                // means the list was empty before n was inserted
        L->back = n; // so sets L->back to n as well, as list now only includes one element
    }
    L->length++; // increments length of list by 1
    if (L->index >= 0)
    {
        L->index++; // increments index by 1 to maintain its position relative to the new front inserted element
    }
}

// Insert new element into L. If L is non-empty, insertion takes place after back element.
void append(List L, int x)
{
    if (L == NULL)
    {
        fprintf(stderr, "Error: calling append() on NULL List\n");
        return;
    }
    Node n = malloc(sizeof(NodeObj));
    n->data = x;
    n->next = NULL;    // node is at the end, so next pointer will be NULL
    n->prev = L->back; // node's prev pointer will point to the list's current last element (which is now the second to last element)
    if (L->back != NULL)
    {                      // if list is not empty
        L->back->next = n; // the current last item of list's 'next' pointer will now point to n, which is now the last item
    }
    L->back = n; // updates list so that back item is now n, which was inserted at back of list
    if (L->front == NULL)
    {                 // means the list was empty before insertion
        L->front = n; // then n is also the front of list (only element in list), so front pointer should also point to n
    }
    L->length++; // increments length of list by 1
} // The cursor index will remain the same because the cursor still points to the same element it was pointing to before appending

// Insert new element before cursor.
// Pre: length()>0, index(()>=0
void insertBefore(List L, int x)
{
    if (L == NULL)
    {
        fprintf(stderr, "Error: calling insertBefore() on NULL List\n");
        return;
    }
    if (length(L) <= 0)
    {
        fprintf(stderr, "Error: calling insertBefore() on empty List\n");
        return;
    }
    if (index(L) < 0)
    {
        fprintf(stderr, "Error: calling insertBefore() on undefined cursor\n");
        return;
    }
    Node n = malloc(sizeof(NodeObj));
    n->data = x;
    n->next = L->cursor;       // the inserted node's 'next' pointer will point to where the cursor is in the list
    n->prev = L->cursor->prev; // the inserted node's 'prev' pointer will point to where the cursor's 'prev' pointer was pointing to
    if (L->cursor->prev != NULL)
    {                              // if cursor is not at the front
        L->cursor->prev->next = n; // the element that the cursor's 'prev' pointer was pointing to should now update its 'next' pointer to point to the inserted n
    }
    L->cursor->prev = n; // updates cursor's 'prev' pointer to point to n
    if (L->cursor == L->front)
    {                 // if cursor is at the front
        L->front = n; // the front of list is now n, because n was inserted in front of the cursor
    }
    L->length++; // increment length of list by 1
    L->index++;  // to maintain position of cursor, must increment index by 1
}

// Insert new element after cursor.
// Pre: length()>0, index(()>=0
void insertAfter(List L, int x)
{
    if (L == NULL)
    {
        fprintf(stderr, "Error: calling insertAfter() on NULL List\n");
        return;
    }
    if (length(L) <= 0)
    {
        fprintf(stderr, "Error: calling insertAfter() on empty List\n");
        return;
    }
    if (index(L) < 0)
    {
        fprintf(stderr, "Error: calling insertAfter() on undefined cursor\n");
        return;
    }
    Node n = malloc(sizeof(NodeObj));
    n->data = x;
    n->next = L->cursor->next; // n's 'next' pointer will point to where cursor's 'next' was pointing
    n->prev = L->cursor;       // n's 'prev' pointer will point to cursor
    if (L->cursor->next != NULL)
    {                              // if cursor is not at the back
        L->cursor->next->prev = n; // then the element that the cursor's 'next' pointer was pointing to should now update its 'prev' pointer to point to the inserted n
    }
    L->cursor->next = n; // update cursor's next pointer to point to n
    if (L->cursor == L->back)
    {                // if cursor is at the back
        L->back = n; // then inserted n will now be the back of list, so update L->back
    }
    L->length++; // increment length
} //        do not need to increment index as cursor will stay in same position

// Delete the front element. Pre: length()>0
void deleteFront(List L)
{
    if (L == NULL)
    {
        fprintf(stderr, "Error: calling deleteFront() on NULL List\n");
        return;
    }
    if (length(L) <= 0)
    {
        fprintf(stderr, "Error: calling deleteFront() on empty List\n");
        return;
    }
    Node n = L->front;
    if (L->front == L->back)
    { // only one element, so lots of cleanup
        L->front = NULL;
        L->back = NULL;
        L->cursor = NULL;
        L->index = -1;
    }
    else
    {
        L->front = L->front->next;
        L->front->prev = NULL;
        if (L->cursor != NULL)
        { // if cursor is defined, we need to update its index
            L->index--;
        }
    }
    L->length--;
    free(n);
}

// Delete the back element. Pre: length()>0
void deleteBack(List L)
{
    if (L == NULL)
    {
        fprintf(stderr, "Error: calling deleteBack() on NULL List\n");
        return;
    }
    if (length(L) <= 0)
    {
        fprintf(stderr, "Error: calling deleteBack() on empty List\n");
        return;
    }
    Node n = L->back; // make node n be the last item in the list
    if (L->front == L->back)
    {                    // only one element in list
        L->front = NULL; // reset all fields to indicate empty list
        L->back = NULL;
        L->cursor = NULL;
        L->index = -1;
    }
    else
    {
        L->back = L->back->prev; // L->back will now be equal to what the last element in the list's 'prev' pointer was pointing to (effectively the second-to-last item in the list)
        L->back->next = NULL;    // set this element's next pointer to NULL as it is now the end of the list
        if (L->cursor == n)
        {                     // if cursor is at the back
            L->cursor = NULL; // nullify cursor since n is deleted, and cursor was pointing to n
            L->index = -1;    // set cursor index to -1 (reset)
        }
    }
    L->length--; // item was deleted from list so must decrement length by 1
    free(n);     // free n as it was deleted
}

// Delete cursor element, making cursor undefined.
// Pre: length()>0, index(()>=0
void delete(List L)
{
    if (L == NULL)
    {
        fprintf(stderr, "Error: calling delete() on NULL List\n");
        return;
    }
    if (length(L) <= 0)
    {
        fprintf(stderr, "Error: calling delete() on empty List\n");
        return;
    }
    if (index(L) < 0)
    {
        fprintf(stderr, "Error: calling delete() on undefined cursor\n");
        return;
    }
    Node n = L->cursor; // make node n equal to where the cursor is pointing
    if (L->cursor == L->front)
    { // if cursor is at the front, delete the front item
        deleteFront(L);
    }
    else if (L->cursor == L->back)
    {
        deleteBack(L); // if at back, delete back item
    }
    else
    {
        L->cursor->prev->next = L->cursor->next; // we need to update the 'next' pointer of the element that
                                                 // the cursor's 'prev' pointer was pointing to. we set this
                                                 // to where the cursor's 'next' pointer was pointing.
                                                 // essentially, we are bypassing the cursor element.
        L->cursor->next->prev = L->cursor->prev; // we do the same thing by updating the 'prev' pointer
                                                 //  that the cursor's 'next' pointer was pointing to, so that this
                                                 //  elem's 'prev' pointer is now pointing to where the cursor's
                                                 //  'prev' pointer was pointing (again bypassing the cursor elem)
        L->cursor = NULL; // reset cursor to NULL
        L->index = -1;    // reset cursor index to -1
        L->length--;      // cursor elem was deleted so decrement length of list by 1
        free(n);          // free n since cursor elem was deleted
    }
}

void printList(FILE *out, List L)
{
    if (L == NULL)
    {
        fprintf(stderr, "Error: calling printList() on NULL List\n");
        return;
    }
    Node n = L->front; // make n the pointer pointing to front of list
    while (n != NULL)
    {                                // as long as n is not NULL:
        fprintf(out, "%d", n->data); // Print the value stored in the index member of the node
        if (n->next != NULL)
        {                      // Check if there is a next node
            fprintf(out, " "); // If so, print a space
        }
        n = n->next; // Move the pointer to the next node
    }
}

// Returns a new List representing the same integer
// sequence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L. The state
// of L is unchanged.
List copyList(List L)
{
    if (L == NULL)
    {
        fprintf(stderr, "Error: calling copyList() on NULL List\n");
        return NULL;
    }
    List copy = newList(); // make a new list called copy
    Node n = L->front;     // set n to point to front of list
    while (n != NULL)
    {                          // as long as n is not null:
        append(copy, n->data); // add index value pointed to by n to the back of list
        n = n->next;           // keep iterating by moving pointer so that n points to where n->next was pointing}
    }
    return copy; // return new list copy
}
