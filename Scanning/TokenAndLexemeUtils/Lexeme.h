//
// Created by dpmar on 7/31/2022.
//

#ifndef ENGINEERING_A_COMPILER_LEXEME_H
#define ENGINEERING_A_COMPILER_LEXEME_H

#include <string>
#include <utility>
#include <iostream>

using std::string;

class Lexeme {
private:
    string label;
    string regex;
    unsigned int precedence;

public:
    Lexeme(string mLabel, string mRegex, unsigned int mPrecedence) {
        label = std::move(mLabel);
        regex = std::move(mRegex);
        precedence = mPrecedence;
    }

    Lexeme() {precedence = 0;}

    inline string getLabel() { return label; }
    inline string getRegex() { return regex; }

    inline unsigned int getPrecedence() const { return precedence; }

    inline void printLexeme() { std::cout << "Lexeme label: " << label <<
    " Regex: " << regex << " Precedence: " << precedence << "\n"; }

};


#endif //ENGINEERING_A_COMPILER_LEXEME_H
