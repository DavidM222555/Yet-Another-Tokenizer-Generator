//
// Created by dpmar on 7/31/2022.
//

#ifndef ENGINEERING_A_COMPILER_FILEREADER_H
#define ENGINEERING_A_COMPILER_FILEREADER_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "Lexeme.h"

using std::string;
using std::vector;

class FileReader {
private:
    vector<Lexeme> lexemes;

public:
    void getLexemesFromFile(const string& fileName);
    void printLexemes();
};


#endif //ENGINEERING_A_COMPILER_FILEREADER_H
