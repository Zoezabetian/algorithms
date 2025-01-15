#include <iostream>
#include <string>
#include <iomanip> // For std::setw

#include "List.h"

using namespace std;

// shuffle function
void shuffle(List &D)
{
    List left, right;
    int midpoint = D.length() / 2; // works for both even and odd lengths
    D.moveFront();
    right.moveFront();
    left.moveFront();
    for (int i = 0; i < midpoint; i++)
    {
        left.insertBefore(D.peekNext());
        D.moveNext();
    }

    while (D.position() < D.length())
    {
        right.insertBefore(D.peekNext());
        D.moveNext();
    }

    D.clear();

    left.moveFront();
    right.moveFront();
    D.moveFront();

    while (left.position() < left.length() || right.position() < right.length())
    {
        if (right.position() < right.length())
        {
            D.insertBefore(right.peekNext());
            right.moveNext();
        }
        if (left.position() < left.length())
        {
            D.insertBefore(left.peekNext());
            left.moveNext();
        }
    }
}

// helper function for counting shuffles
int dealer(List &D, List &original, int shuffleCount)
{
    shuffle(D);
    shuffleCount++;

    if (D.equals(original))
    {
        return shuffleCount;
    }
    else
    {
        return dealer(D, original, shuffleCount); // recursive call with the updated shuffleCount
    }
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cout << "Usage: " << argv[0] << " <deck size>" << endl;
        return 1;
    }
    cout << "deck size       shuffle count" << endl;
    cout << "------------------------------" << endl;

    int deckSize = atoi(argv[1]);
    List original;
    int shuffleCount = 0;

    for (int i = 1; i <= deckSize; i++)
    {
        original.insertBefore(i);
        List D = original; // make a copy
        int totalShuffles = dealer(D, original, shuffleCount); // call helper func
        if (i < 10) {
            cout << " " << i << setw(15) << "" << totalShuffles << endl;
        }
         else if (i < 100) {
            cout << " " << i << setw(14) << "" << totalShuffles << endl;
        }
        else if (i < 1000) {
            cout << " " << i << setw(13) << "" << totalShuffles << endl;
        }
    }

    return 0;
}  