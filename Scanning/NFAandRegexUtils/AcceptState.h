//
// Created by dpmar on 7/31/2022.
//

#ifndef ENGINEERING_A_COMPILER_ACCEPTSTATE_H
#define ENGINEERING_A_COMPILER_ACCEPTSTATE_H

#include <string>
#include <utility>

#include "Node.h"

using std::string;

// Used to define an accept state of an NFA
// Will be used for determining the token that a lexeme corresponds to
class AcceptState {
private:
    string label;
    Node* nodeForAcceptState{};

public:
    AcceptState(string sLabel, Node* sNodeForAcceptState) { label = std::move(sLabel); nodeForAcceptState = sNodeForAcceptState; }

    inline string getLabel() { return label; }
    inline Node* getNode() { return nodeForAcceptState; }
};


#endif //ENGINEERING_A_COMPILER_ACCEPTSTATE_H
