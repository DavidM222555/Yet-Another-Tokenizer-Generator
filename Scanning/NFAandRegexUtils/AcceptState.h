//
// Created by dpmar on 7/31/2022.
//

#ifndef ENGINEERING_A_COMPILER_ACCEPTSTATE_H
#define ENGINEERING_A_COMPILER_ACCEPTSTATE_H

#include <string>
#include <utility>

#include "Node.h"
#include "FileHandling/Lexeme.h"

using std::string;

// Used to define an accept state of an NFA
// Will be used for determining the token that a lexeme corresponds to
class AcceptState {
private:
    Lexeme lexeme;
    Node* nodeForAcceptState{};

public:
    AcceptState(Lexeme mLexeme, Node* mNodeForAcceptance) {
        lexeme = std::move(mLexeme);
        nodeForAcceptState = mNodeForAcceptance;
    }

    inline Lexeme getLexeme() { return lexeme; }
    inline Node* getNode() { return nodeForAcceptState; }
};


#endif //ENGINEERING_A_COMPILER_ACCEPTSTATE_H
