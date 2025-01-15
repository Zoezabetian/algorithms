#include <iostream>
#include <fstream>
#include <string>
#include "Dictionary.h" 

using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
        return 1;
    }

    ifstream inputFile(argv[1]);
    if (!inputFile) {
        cerr << "Error: Unable to open input file: " << argv[1] << endl;
        return 1;
    }

    ofstream outputFile(argv[2]);

    Dictionary dict;
    string line;
    int lineNumber = 1;
    while (getline(inputFile, line)) {
        dict.setValue(line, lineNumber++); // Insert string as key into Dictionary, with line number as value
    }

    inputFile.close(); // Close the input file after reading all lines

    // Use Dictionary's to_string method for the first representation
    string firstRepresentation = dict.to_string();
    outputFile << firstRepresentation << endl;



    // Use Dictionary's pre_string method for the second representation
    string secondRepresentation = dict.pre_string();
    outputFile << secondRepresentation << endl;

    outputFile.close(); // Close the output file

    return 0;
}
