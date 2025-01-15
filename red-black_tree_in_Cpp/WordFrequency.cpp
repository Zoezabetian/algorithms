#include <algorithm> 
#include <iostream>
#include <fstream>
#include <string>
#include "Dictionary.h" // Include the Dictionary class header

using namespace std;

void processLine(const string &line, Dictionary &dictionary)
{
    size_t begin, end, len;
    string token;
    string delim = " \t\\\"\',<.>/?;:[{]}|`~!@#$^&*%()-_=+0123456789";
    

    len = line.length();
    begin = min(line.find_first_not_of(delim, 0), len);
    end = min(line.find_first_of(delim, begin), len);
    token = line.substr(begin, end - begin);

    while (token != "")
    { // we have a token
        // Update dictionary
        transform(token.begin(), token.end(), token.begin(), ::tolower);
        if (!token.empty())
        {
            if (dictionary.contains(token))
            {
                // Word already exists, increment frequency
                dictionary.getValue(token)++;
            }
            else
            {
                // New word, set frequency to 1
                dictionary.setValue(token, 1);
            }
        }

        // get next token
        begin = min(line.find_first_not_of(delim, end + 1), len);
        end = min(line.find_first_of(delim, begin), len);
        token = line.substr(begin, end - begin);
    }
}

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
        cerr << "Error: Unable to open input file." << endl;
        return 1;
    }

    if (!outputFile)
    {
        cerr << "Error: Unable to open output file." << endl;
        return 1;
    }

    Dictionary wordFrequency;

    string line;
    while (getline(inputFile, line))
    {
        processLine(line, wordFrequency);
    }

    // Output results to file
    outputFile << wordFrequency.to_string();

    inputFile.close();
    outputFile.close();

    return 0;
}
