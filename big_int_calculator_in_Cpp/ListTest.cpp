#include <iostream>
#include "List.h"

using namespace std;

int main()
{

    List myList;
    cout << "Attempting to insert elements after cursor:" << endl;
    myList.moveFront();
    myList.insertAfter(60);
    myList.insertAfter(50);
    myList.insertAfter(40);
    myList.insertAfter(30);
    myList.insertAfter(20);
    myList.insertAfter(10);

    cout << "\nExpected List: (10, 20, 30, 40, 50, 60)" << endl;
    cout << "My List: " << myList.to_string() << endl;

    cout << "Cursor position after insertAfter: " << myList.position() << endl;

    cout << "\nAttempting to insert element before cursor:" << endl;
    myList.insertBefore(5);
    cout << "Expected List: (5, 10, 20, 30, 40, 50, 60)" << endl;
    cout << "My List: " << myList.to_string() << endl;
    cout << "Cursor position after insertBefore: " << myList.position() << endl;
    cout << "" << endl;

    cout << "\nAttempting to moveBack." << endl;
    myList.moveBack();
    cout << "Cursor position after moveBack: " << myList.position() << endl;

    myList.movePrev();
    cout << "" << endl;

    myList.movePrev();
    cout << "" << endl;

    myList.movePrev();

    // Copy the list
    List copiedList(myList);
    cout << "List: " << myList.to_string() << endl;
    cout << "Copied List: " << copiedList.to_string() << endl;
    // Verify that the copied list is the same as the original list
    if (myList.to_string() == copiedList.to_string())
    {
        cout << "Copied list matches the original list." << endl;
    }
    else
    {
        cout << "Error: Copied list does not match the original list." << endl;
    }
    cout << "\nFind next occurrence of 50:" << endl;
    myList.findNext(50);
    cout << "Cursor position after findNext(50): " << myList.position() << endl;

    cout << "My List: " << myList.to_string() << endl;

    cout << "\nFind previous occurrence of 10:" << endl;
    myList.findPrev(10);
    cout << "Cursor position after findPrev(10): " << myList.position() << endl;
    cout << "My List: " << myList.to_string() << endl;

    cout << "\nAttempting to moveBack." << endl;
    myList.moveBack();
    cout << "Cursor position after moveBack: " << myList.position() << endl;

    cout << "\nAttempting to moveFront." << endl;
    myList.moveFront();
    cout << "Cursor position after movFront: " << myList.position() << endl;

    cout << "" << endl;

    myList.moveNext();
    cout << "" << endl;

    myList.moveNext();
    cout << "" << endl;

    myList.moveNext();
    cout << "My List: " << myList.to_string() << endl;
    cout << "Cursor position after moving Next: " << myList.position() << endl;

    cout << "\nErase element after cursor:" << endl;
    myList.eraseAfter();
    cout << "Expected List after eraseAfter: (5, 10, 20, 40, 50, 60)" << endl;
    cout << "My List: " << myList.to_string() << endl;

    cout << "Cursor position after eraseAfter: " << myList.position() << endl;

    cout << "\nErase element before cursor:" << endl;
    myList.eraseBefore();
    cout << "Expected List after eraseBefore: (5, 10, 40, 50, 60)" << endl;
    cout << "My List: " << myList.to_string() << endl;

    cout << "\nCursor position: " << myList.position() << endl;

    cout << "\nInserting element 10 after cursor." << endl;
    myList.insertAfter(10);
    cout << "My List: " << myList.to_string() << endl;
    cout << "Cursor position: " << myList.position() << endl;

    cout << "\nInserting element 10 before cursor." << endl;
    myList.insertBefore(10);

    cout << "My List: " << myList.to_string() << endl;
    cout << "Cursor position: " << myList.position() << endl;

    cout << "\nCleanup List (removing duplicates):" << endl;
    myList.cleanup();
    cout << "List after cleanup: " << myList.to_string() << endl;
    cout << "Cursor position after cleanup: " << myList.position() << endl;

    List anotherList;
    anotherList.insertAfter(40);
    anotherList.insertAfter(50);
    cout << "\nAnotherList: " << anotherList.to_string() << endl;
    cout << "Going to concatenate myList and anotherList..." << endl;
    cout << "" << endl;

    List concatenatedList = myList.concat(anotherList);
    cout << "\nConcatenated List: " << concatenatedList.to_string() << endl;

    cout << "Concat cursor position: " << concatenatedList.position() << endl;
concatenatedList.moveBack();
    cout << "Moving back. New position: " << concatenatedList.position() << endl;
    cout << "\nTesting setBefore on concatenated list. Changing beforeCursor to 15." << endl;
    concatenatedList.setBefore(15);
    cout << "\nConcatenated List: " << concatenatedList.to_string() << endl;
    cout << "Concat cursor position: " << concatenatedList.position() << endl;

    cout << "" << endl;
    concatenatedList.movePrev();
    cout << "" << endl;

    concatenatedList.movePrev();
    cout << "Concat cursor position after moving 2 previous: " << concatenatedList.position() << endl;

    cout << "\nTesting setAfter on concatenated list. Changing afterCursor to 25." << endl;
    concatenatedList.setAfter(25);
    cout << "Concatenated List: " << concatenatedList.to_string() << endl;
    cout << "Concat cursor position: " << concatenatedList.position() << endl;

    cout << "\nTesting front on concatenated list: " << concatenatedList.front() << endl;
    cout << "\nTesting back on concatenated list: " << concatenatedList.back() << endl;
    cout << "" << endl;

    cout << "Concat cursor position: " << concatenatedList.position() << endl;
    cout << "\nTesting peekNext on concatenated list: " << concatenatedList.peekNext() << endl;
    cout << "\nTesting peekPrev on concatenated list: " << concatenatedList.peekPrev() << endl;

    cout << "\nTesting length on concatenated list: " << concatenatedList.length() << endl;

    cout << "\nTesting equals on two lists." << endl;
    cout << "Concatenated List: " << concatenatedList.to_string() << endl;

    List testList1;
    testList1.insertAfter(15);
    testList1.insertAfter(25);
    testList1.insertAfter(60);
    testList1.insertAfter(50);
    testList1.insertAfter(40);
    testList1.insertAfter(10);
    testList1.insertAfter(5);
    cout << "Test List 1: " << testList1.to_string() << endl;

    List testList2;
    testList2.insertAfter(15);
    testList2.insertAfter(25);
    testList2.insertAfter(60);
    testList2.insertAfter(5);
    testList2.insertAfter(40);
    testList2.insertAfter(10);
    testList2.insertAfter(5);
    cout << "Test List 2: " << testList2.to_string() << endl;

    cout << "\nTesting if concatenated list and test list 1 are equal (should be true): " << boolalpha << concatenatedList.equals(testList1) << endl;
    cout << "\nTesting if concatenated list and test list 2 are equal (should be false): " << boolalpha << concatenatedList.equals(testList2) << endl;

    cout << "\nTesting clear on concatenated list:" << endl;
    concatenatedList.clear();
    cout << "Concatenated List: " << concatenatedList.to_string() << endl;

    cout << "\nInserting element 10 before cursor." << endl;
    concatenatedList.insertBefore(10);
    cout << "" << endl;
    cout << "Concatenated List: " << concatenatedList.to_string() << endl;

    concatenatedList.movePrev();
    cout << "Cursor position after moving prev: " << concatenatedList.position() << endl;

    cout << "" << endl;
    cout << "\nInserting element 5 before cursor." << endl;
    concatenatedList.insertBefore(5);
    cout << "Cursor position after insertBefore: " << concatenatedList.position() << endl;

    cout << "Concatenated List: " << concatenatedList.to_string() << endl;

    cout << "\nClearing list:" << endl;
    concatenatedList.clear();
    cout << "List: " << concatenatedList.to_string() << endl;
    cout << "Cursor position before inserting: " << concatenatedList.position() << endl;

    cout << "\nInserting element 10 after cursor." << endl;
    concatenatedList.insertAfter(10);
    cout << "" << endl;
    cout << "List: " << concatenatedList.to_string() << endl;
    cout << "Cursor position after inserting: " << concatenatedList.position() << endl;

    concatenatedList.moveNext();
    cout << "Cursor position after moving next: " << concatenatedList.position() << endl;

    cout << "" << endl;
    cout << "\nInserting element 5 after cursor." << endl;
    concatenatedList.insertAfter(5);
    cout << "Cursor position after insertAfter: " << concatenatedList.position() << endl;

    cout << "List: " << concatenatedList.to_string() << endl;

    cout << "" << endl;
    cout << "\nErasing element after cursor." << endl;
    concatenatedList.eraseAfter();
    cout << "Cursor position after eraseAfter: " << concatenatedList.position() << endl;
    cout << "List: " << concatenatedList.to_string() << endl;
    cout << "" << endl;
    cout << "\nErasing element before cursor." << endl;
    concatenatedList.eraseBefore();
    cout << "Cursor position after eraseBefore: " << concatenatedList.position() << endl;
    cout << "List: " << concatenatedList.to_string() << endl;

    // Test for Empty_size
    cout << "\nTesting Empty_size:" << endl;
    List A;
    if (A.length() != 0)
    {
        cout << "Test Empty_size failed." << endl;
    }
    else
    {
        cout << "Test Empty_size passed." << endl;
    }

    // Continue with other test cases in a similar manner...

    // InsertAfter_size test
    cout << "\nTesting InsertAfter_size:" << endl;
    // Reset List A or use a new List variable if you want to keep tests independent
    A.insertAfter(1);
    A.insertAfter(2);
    A.insertAfter(3);
    A.insertAfter(5);
    A.insertAfter(12);
    if (A.length() != 5)
    {
        cout << "Test InsertAfter_size failed." << endl;
    }
    else
    {
        cout << "Test InsertAfter_size passed." << endl;
    }

    cout << "\nTesting InsertBefore_size:" << endl;
    List B;
    B.insertBefore(1);
    B.insertBefore(2);
    B.insertBefore(3);
    B.insertBefore(5);
    B.insertBefore(12);
    if (B.length() != 5)
    {
        cout << "Test InsertBefore_size failed." << endl;
    }
    else
    {
        cout << "Test InsertBefore_size passed." << endl;
    }

    cout << "\nTesting EraseAfter_size:" << endl;
    List C;
    // Insert some elements
    C.insertBefore(1);
    C.insertBefore(2);
    C.insertBefore(3);
    C.insertBefore(5);
    C.insertBefore(12);
    // Now erase some and check size
    C.movePrev(); // Move cursor to a position where eraseAfter can be called
    C.eraseAfter();
    if (C.length() != 4)
        return 1;
    C.findPrev(2); // Assuming findPrev sets the cursor correctly
    C.eraseAfter();
    if (C.length() != 3)
    {
        cout << "Test EraseAfter_size failed." << endl;
    }
    else
    {
        cout << "Test EraseAfter_size passed." << endl;
    }

    cout << "\nTesting EraseBefore_size:" << endl;
    List D;
    // Insert some elements
    D.insertAfter(1);
    D.insertAfter(2);
    D.insertAfter(3);
    D.insertAfter(5);
    D.insertAfter(12);
    // Now erase some and check size
    D.moveNext(); // Move cursor to a position where eraseBefore can be called
    D.eraseBefore();
    if (D.length() != 4)
        return 1;
    D.findNext(2); // Assuming findNext sets the cursor correctly
    D.eraseBefore();
    if (D.length() != 3)
    {
        cout << "Test EraseBefore_size failed." << endl;
    }
    else
    {
        cout << "Test EraseBefore_size passed." << endl;
    }


    return 0;
}
