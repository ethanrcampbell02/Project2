#include "Lexer/Lexer.h"
#include "Parser/Parser.h"
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

int main(int argc, char** argv) {

    // Check command line arguments
    if (argc != 2) {
        cout << "usage: " << argv[0] << " input_file" << endl;
        return 1;
    }

    // Open file
    string fileName = argv[1];
    ifstream inputFile(fileName);

    if (!inputFile.is_open()) {
        cout << "File " << fileName << " could not be found or opened." << endl;
        return 1;
    }

    // Read file into string variable "input"
    stringstream ss;
    ss << inputFile.rdbuf();
    string input = ss.str();
    Lexer* lexer = new Lexer();
    lexer->Run(input);

    // Parse the vector of Tokens
    Parser* parser = new Parser();
    DatalogProgram* datalogProgram = parser->Parse(lexer->GetTokens());

    datalogProgram->ToString();

    delete parser;
    delete lexer;

    return 0;
}