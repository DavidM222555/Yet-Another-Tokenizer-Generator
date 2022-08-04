//
// Created by dpmar on 7/31/2022.
//

#include "FileReader.h"
#include <sstream>
#include <vector>

vector<Lexeme> FileReader::getLexemesFromFile(const string& fileName) {
    std::ifstream readFile (fileName);

    // Used for detecting when we have found the start of the lexeme specification in the file
    auto lexemesReadyToGather = false;

    if(readFile.is_open()) {
        string line;

        while (std::getline(readFile, line)) {
            if(line == "$LEXEMES") {
                lexemesReadyToGather = true;
            } else if(line == "$$LEXEMES") {
                lexemesReadyToGather = false;
            } else if(lexemesReadyToGather) {
                std::stringstream delimitedString(line);
                string segment;

                string lexemeLabel;
                string regexLabel;
                int precedence;

                int count = 0;

                while(getline(delimitedString, segment, ',')) {
                    if(count == 0) {
                        lexemeLabel = segment;
                    }
                    else if(count == 1) {
                        regexLabel = segment;
                    }
                    else
                    {
                        precedence = std::stoi(segment);
                    }

                    count++;
                }

                Lexeme lexemeToAdd(lexemeLabel, regexLabel, precedence);

                lexemes.push_back(lexemeToAdd);
            }
        }
    }

    return lexemes;
}

void FileReader::printLexemes() {
    for(auto lexeme : lexemes) {
        lexeme.printLexeme();
    }
}