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

// Used to define an accept state of an NFA.
// Will be used for determining the lexeme that a given token/state in an NFA corresponds to.
class AcceptState {
private:
    Lexeme lexeme;
    Node* nodeForAcceptState{};

public:
    // The basic constructor of an accept state is the lexeme that it represents
    // and the node that is an accept state for that lexeme's branch of the NFA.
    // Note: We can guarantee that every lexeme only contributes one accept state to the tokenizer NFA
    // and this is due to the way Thompson's construction builds out NFA by progressively only having one
    // accept state for any NFA at any point.
    AcceptState(Lexeme mLexeme, Node* mNodeForAcceptance) {
        lexeme = std::move(mLexeme);
        nodeForAcceptState = mNodeForAcceptance;
    }

    inline Lexeme getLexeme() { return lexeme; }
    inline Node* getNode() { return nodeForAcceptState; }
};


#endif //ENGINEERING_A_COMPILER_ACCEPTSTATE_H
