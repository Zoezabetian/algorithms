#include <iostream>
#include <fstream>
#include <string>
#include "LargeInt.h"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
        return 1;
    }

    ifstream inputFile(argv[1]);
    ofstream outputFile(argv[2]);

    if (!inputFile)
    {
        cerr << "Error: Unable to open input file: " << argv[1] << endl;
        return 1;
    }

    if (!outputFile)
    {
        cerr << "Error: Unable to open output file: " << argv[2] << endl;
        return 1;
    }

    string line1, line2, line3;

    if (getline(inputFile, line1))
    {
        getline(inputFile, line2);

        if (getline(inputFile, line3))
        {
            LargeInt A(line1);
            LargeInt B(line3);

            outputFile << A << endl
                       << endl;
            outputFile << B << endl
                       << endl;
            outputFile << (A + B) << endl
                       << endl;
            outputFile << (A - B) << endl
                       << endl;
            outputFile << (A - A) << endl
                       << endl;
            outputFile << (3 * A - 2 * B) << endl
                       << endl;
            outputFile << (A * B) << endl
                       << endl;
            outputFile << (A * A) << endl
                       << endl;
            outputFile << (B * B) << endl
                       << endl;
            outputFile << (9 * A * A * A * A + 16 * B * B * B * B * B) << endl;
        }
        else
        {
            cerr << "Error: Input file does not contain a third line." << endl;
            return 1;
        }
    }
    else
    {
        cerr << "Error: Input file is empty." << endl;
        return 1;
    }

    inputFile.close();
    outputFile.close();

    return 0;
}
