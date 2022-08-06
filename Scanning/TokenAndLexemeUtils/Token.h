//
// Created by dpmar on 8/3/2022.
//

#ifndef ENGINEERING_A_COMPILER_TOKEN_H
#define ENGINEERING_A_COMPILER_TOKEN_H

#include <string>
#include "Lexeme.h"

using std::string;

class Token {
private:
    Lexeme lexemeForToken;
    string tokenString;

public:
    Token(Lexeme mLexemeForToken, string mTokenString) {
        lexemeForToken = mLexemeForToken;
        tokenString = mTokenString;
    }

    Token() { lexemeForToken = Lexeme(); tokenString = ""; }

    inline Lexeme getLexemeForToken() { return lexemeForToken; };
    inline string getTokenString() { return tokenString; }

};


#endif //ENGINEERING_A_COMPILER_TOKEN_H
