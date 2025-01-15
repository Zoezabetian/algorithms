#include <iostream>
#include <string>
#include "List.h"

List::Node::Node(ListElement x) : data(x), next(nullptr), prev(nullptr) {}

// Class Constructors & Destructors ----------------------------------------

// Constructor
List::List()
    : frontDummy(new Node(-1)), backDummy(new Node(-1)), pos_cursor(0), num_elements(0)
{
    frontDummy->next = backDummy; // Initialize list as empty with dummy nodes connected
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy; // Initialize cursor to reflect an empty list
    afterCursor = backDummy;
}

// Copy constructor
List::List(const List &L)
    : frontDummy(new Node(-1)), backDummy(new Node(-1)), pos_cursor(L.pos_cursor), num_elements(L.num_elements)
{
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    Node *current = L.frontDummy->next;
    Node *prevNew = frontDummy;
    while (current != L.backDummy)
    {
        Node *newNode = new Node(current->data);
        newNode->prev = prevNew;
        prevNew->next = newNode;
        prevNew = newNode;
        current = current->next;
    }
    prevNew->next = backDummy;
    backDummy->prev = prevNew;

    // Reposition cursor in the newly created list
    beforeCursor = frontDummy;
    afterCursor = frontDummy->next; // This effectively sets it to the first real node or backDummy if list is empty
    for (int i = 0; i < pos_cursor && afterCursor != backDummy; ++i)
    {
        beforeCursor = afterCursor;
        afterCursor = afterCursor->next;
    }
}

// Destructor
List::~List()
{
    // Delete all nodes except the dummy nodes
    clear();
    // Delete the dummy nodes
    delete frontDummy;
    delete backDummy;
}

// Access functions --------------------------------------------------------

// length()
// Returns the length of this List.
int List::length() const
{
    return num_elements;
}

// front()
// Returns the front element in this List.
// pre: length()>0
ListElement List::front() const
{
    if (length() > 0)
    {
        return frontDummy->next->data;
    }
    else
    {
        // handle the case when the list is empty
        throw std::length_error("List: front(): empty list");
    }
}

// back()
// Returns the back element in this List.
// pre: length()>0
ListElement List::back() const
{
    if (length() > 0)
    {
        return backDummy->prev->data;
    }
    else
    {
        throw std::length_error("List: back(): empty list");
    }
}
// position()
// Returns the position of cursor in this List: 0 <= position() <= length().
int List::position() const
{
    return pos_cursor;
}

// peekNext()
// Returns the element after the cursor.
// pre: position()<length()
ListElement List::peekNext() const
{
    if (position() < length())
    {
        return afterCursor->data;
    }
    else
    {
        throw std::range_error("List: peekNext(): cursor at back");
    }
}

// peekPrev()
// Returns the element before the cursor.
// pre: position()>0
ListElement List::peekPrev() const
{
    if (position() > 0)
    {
        return beforeCursor->data;
    }
    else
    {
        throw std::range_error("List: peekPrev(): cursor at front");
    }
}

// Manipulation procedures -------------------------------------------------

// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::clear()
{
    Node *temp = frontDummy->next;
    while (temp != backDummy)
    {
        Node *next = temp->next;
        delete temp;
        temp = next;
    }
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;
}

// moveFront()
// Moves cursor to position 0 in this List.
void List::moveFront()
{
    if (num_elements > 0)
    {
        if (beforeCursor == frontDummy)
        {
            //std::cout << "Cursor is already at front." << std::endl;
            return;
        }

        beforeCursor = frontDummy;
        afterCursor = frontDummy->next;
        pos_cursor = 0;
    }
}

// moveBack()
// Moves cursor to position length() in this List.
void List::moveBack()
{
    if (num_elements > 0)
    {
        if (afterCursor == backDummy)
        {
            //std::cout << "Cursor is already at back." << std::endl;
            return;
        }
        beforeCursor = backDummy->prev;
        afterCursor = backDummy;
        pos_cursor = num_elements;
    }
}

// moveNext()
// Advances cursor to next higher position. Returns the List element that
// was passed over.
// pre: position()<length()
ListElement List::moveNext()
{
    if (position() < length())
    {
        beforeCursor = beforeCursor->next;
        afterCursor = afterCursor == nullptr ? backDummy : afterCursor->next;

        pos_cursor++;
        return beforeCursor->data;
    }
    else
    {
        throw std::range_error("List: moveNext(): cursor at back");
    }
}

// movePrev()
// Advances cursor to next lower position. Returns the List element that
// was passed over.
// pre: position()>0

ListElement List::movePrev()
{
    if (position() > 0)
    {
        afterCursor = afterCursor->prev;
        beforeCursor = beforeCursor == nullptr ? frontDummy : beforeCursor->prev;

        pos_cursor--;
        return afterCursor->data;
    }
    else
    {
        throw std::range_error("List: movePrev(): cursor at front");
    }
}

// insertAfter()
// Inserts x after cursor.
void List::insertAfter(ListElement x)
{
    Node *newNode = new Node(x);
    if (newNode == nullptr)
    {
        throw std::bad_alloc(); // Handle memory allocation failure
    }

    if (num_elements == 0 || afterCursor == backDummy)
    {
        // Inserting into an empty list or end of list
        newNode->prev = backDummy->prev;
        newNode->next = backDummy;
        backDummy->prev->next = newNode;
        backDummy->prev = newNode;
        afterCursor = newNode;
    }
    else
    {
        // Inserting when the list is not empty
        newNode->next = afterCursor;
        newNode->prev = beforeCursor;
        afterCursor->prev = newNode;
        beforeCursor->next = newNode;
        afterCursor = newNode;
    }

    num_elements++;
}

// insertBefore()
// Inserts x before cursor.
void List::insertBefore(ListElement x)
{
    // Allocate a new node with the provided value
    Node *newNode = new Node(x);

    // Insertion when the list is empty or at the beginning of the list
    if (num_elements == 0 || beforeCursor == frontDummy)
    {
        newNode->next = frontDummy->next;
        newNode->prev = frontDummy;
        frontDummy->next->prev = newNode;
        frontDummy->next = newNode;
        beforeCursor = newNode;
    }
    else
    {
        // Insertion in the middle or at the end (but not into an empty list)
        newNode->prev = beforeCursor;
        newNode->next = afterCursor;
        beforeCursor->next = newNode;
        afterCursor->prev = newNode;
        beforeCursor = newNode;
    }
    num_elements++;
    pos_cursor++;
}

// setAfter()
// Overwrites the List element after the cursor with x.
// pre: position()<length()
void List::setAfter(ListElement x)
{

    if (position() < length())
    {
        afterCursor->data = x;
    }
    else
    {
        throw std::range_error("List: setAfter(): cursor at back");
    }
}

// setBefore()
// Overwrites the List element before the cursor with x.
// pre: position()>0
void List::setBefore(ListElement x)
{

    if (position() > 0)
    {
        beforeCursor->data = x;
    }
    else
    {
        throw std::range_error("List: setBefore(): cursor at front");
    }
}

// eraseAfter()
// Deletes element after cursor.
// pre: position()<length()
void List::eraseAfter()
{
    // First, check if the cursor is at a valid position for deletion.
    if (position() < length())
    {
        // Then, check if the node after the cursor is the backDummy, indicating there's nothing to delete.
        if (afterCursor == backDummy)
        {
            throw std::range_error("List: eraseAfter(): at backDummy");
        }

        Node *nodeToDelete = afterCursor;

        // Update links before deletion to bypass the node to be deleted
        beforeCursor->next = nodeToDelete->next;

        if (nodeToDelete->next != backDummy)
        { // Ensure not accessing `prev` of backDummy
            nodeToDelete->next->prev = beforeCursor;
        }
        else
        {
            backDummy->prev = beforeCursor;
        }

        afterCursor = nodeToDelete->next; // Move afterCursor forward before deletion

        delete nodeToDelete;
        num_elements--;
    }
    else
    {
        throw std::range_error("List: eraseAfter(): cursor at back.");
    }
}

// eraseBefore()
// Deletes element before cursor.
// pre: position()>0
void List::eraseBefore()
{
    if (pos_cursor > 0)
    {
        if (beforeCursor == frontDummy)
        {
            throw std::range_error("List: eraseBefore(): cursor at front");
        }

        Node *nodeToDelete = beforeCursor; // Node to delete is indeed beforeCursor

        // Update the links to bypass the nodeToDelete
        if (nodeToDelete->prev != frontDummy)
        { // Ensure there's a node before nodeToDelete
            nodeToDelete->prev->next = afterCursor;
            afterCursor->prev = nodeToDelete->prev;
        }
        else
        { // If nodeToDelete is the first real node
            frontDummy->next = afterCursor;
            afterCursor->prev = frontDummy;
        }

        // Adjust beforeCursor to point to the previous node
        beforeCursor = nodeToDelete->prev;

        delete nodeToDelete; // Delete the target node
        num_elements--;      // Decrement the count of elements
        pos_cursor--;
    }
    else
    {
        throw std::range_error("Cursor is out of range");
    }
}

// Other Functions ---------------------------------------------------------

// findNext()
// Starting from the current cursor position, performs a linear search (in
// the direction front-to-back) for the first occurrence of element x. If x
// is found, places the cursor immediately after the found element, then
// returns the final cursor position. If x is not found, places the cursor
// at position length(), and returns -1.
int List::findNext(ListElement x)
{
    if (num_elements == 0)
    {
        throw std::range_error("Cannot search an empty list");
    }
    // start the search from the current cursor position
    Node *current = afterCursor;
    while (current != backDummy)
    {
        // check if the current node's data matches the target value
        if (current->data == x)
        {
            // update the cursor position to be immediately after the found element
            afterCursor = current->next;
            beforeCursor = current;
            pos_cursor++;

            // return the new cursor position
            return pos_cursor;
        }
        // element not found, repeat
        pos_cursor++;
        current = current->next;
    }
    // if element never found
    afterCursor = backDummy;
    beforeCursor = backDummy->prev;
    pos_cursor = length(); // update cursor to length() per instructions
    return -1;
}

// findPrev()
// Starting from the current cursor position, performs a linear search (in
// the direction back-to-front) for the first occurrence of element x. If x
// is found, places the cursor immediately before the found element, then
// returns the final cursor position. If x is not found, places the cursor
// at position 0, and returns -1.
int List::findPrev(ListElement x)
{
    if (num_elements == 0)
    {
        throw std::range_error("Cannot search an empty list");
    }
    // start the search from the current cursor position
    Node *current = beforeCursor;
    while (current != frontDummy)
    {
        // check if the current node's data matches the target value
        if (current->data == x)
        {
            beforeCursor = current->prev; // update the cursor position to be immediately before the found element
            afterCursor = current;
            pos_cursor--;
            return pos_cursor;
        }
        pos_cursor--;
        current = current->prev;
    }
    // if the target value was not found, place the cursor at position 0 and return -1
    beforeCursor = frontDummy;
    afterCursor = frontDummy->next;
    pos_cursor = 0;
    return -1;
}

// cleanup()
// Removes any repeated elements in this List, leaving only unique elements.
// The order of the remaining elements is obtained by retaining the frontmost
// occurrance of each element, and removing all other occurances. The cursor
// is not moved with respect to the retained elements, i.e. it lies between
// the same two retained elements that it did before cleanup() was called.

void List::cleanup()
{
    int currentPos = 0;
    Node *currentNode = frontDummy->next;

    while (currentNode != backDummy)
    {
        int comparePos = currentPos + 1;
        Node *compareNode = currentNode->next;

        while (compareNode != backDummy)
        {
            if (compareNode->data == currentNode->data)
            {
                Node *nodeToDelete = compareNode;
                compareNode = compareNode->next;

                if (nodeToDelete == beforeCursor)
                {
                    beforeCursor = beforeCursor->prev;
                }
                else if (nodeToDelete == afterCursor)
                {
                    afterCursor = afterCursor->next;
                }
                nodeToDelete->prev->next = nodeToDelete->next;
                nodeToDelete->next->prev = nodeToDelete->prev;
                delete nodeToDelete;
                num_elements--;
                if (comparePos <= pos_cursor)
                    pos_cursor--;
            }
            else
            {
                compareNode = compareNode->next;
            }
            comparePos++;
        }

        currentNode = currentNode->next;
        currentPos++;
    }
}

// concat()
// Returns a new List consisting of the elements of this List, followed by
// the elements of L. The cursor in the returned List will be at postion 0.
List List::concat(const List &L) const
{
    List concatList;
    Node *current = this->frontDummy->next; // Start from the first element of the current list

    // Append elements from the current list to concatList
    while (current != this->backDummy)
    {
        concatList.insertAfter(current->data); // Use insertAfter to append elements
        concatList.moveBack();                 // Move the cursor to the back to keep appending at the end
        current = current->next;
    }

    // Append elements from L to concatList
    Node *Lcurrent = L.frontDummy->next; // Start from the first element of list L
    while (Lcurrent != L.backDummy)
    {
        concatList.insertAfter(Lcurrent->data); // Continue appending elements from L
        concatList.moveBack();                  // Ensure the cursor is at the end for each insertion
        Lcurrent = Lcurrent->next;
    }
    concatList.moveFront();
    // No need to modify pos_cursor of the current list or concatList within this function
    return concatList;
}

// to_string()
// Returns a string representation of this List consisting of a comma
// separated sequence of elements, surrounded by parentheses.
std::string List::to_string() const
{
    Node *current = frontDummy->next;
    std::string result = "(";
    //std::cout << "Inside to_string function:" << std::endl;
    while (current != backDummy)
    {
        //std::cout << "Current data: " << current->data << std::endl;
        result += std::to_string(current->data); // convert data to string and append
        if (current->next != backDummy)
        {
            result += ", ";
        }
        current = current->next;
    }
    result += ")";
    //std::cout << "Result: " << result << std::endl;
    return result; // return string
}



// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List &R) const
{
    if (num_elements != R.num_elements)
    {
        return false;
    }
    Node *current = frontDummy->next;
    Node *Rcurrent = R.frontDummy->next;
    while (current != backDummy && Rcurrent != R.backDummy)
    {
        if (current->data != Rcurrent->data)
        {
            return false;
        }
        current = current->next;
        Rcurrent = Rcurrent->next;
    }
    return true;
}

// Overriden Operators -----------------------------------------------------
std::ostream &operator<<(std::ostream &stream, const List &L)
{
    stream << L.to_string();
    return stream;
}

bool operator==(const List &L, const List &R)
{
    return L.equals(R);
}

List &List::operator=(const List &L)
{
    if (this != &L)
    {
        List temp(L);
        std::swap(frontDummy, temp.frontDummy);
        std::swap(backDummy, temp.backDummy);
        std::swap(beforeCursor, temp.beforeCursor);
        std::swap(afterCursor, temp.afterCursor);
        std::swap(pos_cursor, temp.pos_cursor);
        std::swap(num_elements, temp.num_elements);
    }
    return *this;
}
