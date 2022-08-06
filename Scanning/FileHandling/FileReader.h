//
// Created by dpmar on 7/31/2022.
//

#ifndef ENGINEERING_A_COMPILER_FILEREADER_H
#define ENGINEERING_A_COMPILER_FILEREADER_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "TokenAndLexemeUtils/Lexeme.h"

using std::string;
using std::vector;

class FileReader {
private:
    vector<Lexeme> lexemes;

public:
    // Scans a file with the given name and generates lexemes based off the content of the text.
    // Lexeme files should have the following form:
    // $LEXEMES
    // LexemeName,Regex,Precedence
    // ...
    // $$LEXEMES
    vector<Lexeme> getLexemesFromFile(const string& fileName);

    // Simple helper function for printing the lexemes we currently have
    void printLexemes();
};


#endif //ENGINEERING_A_COMPILER_FILEREADER_H
