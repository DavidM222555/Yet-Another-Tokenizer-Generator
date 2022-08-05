//
// Created by dpmar on 7/28/2022.
//

#ifndef ENGINEERING_A_COMPILER_NFA_H
#define ENGINEERING_A_COMPILER_NFA_H

#include <vector>
#include <string>

#include "Node.h"
#include "NFAandRegexUtils/AcceptState.h"
#include "FileHandling/Lexeme.h"

using std::vector;
using std::string;

class NFA {
private:
    Node* acceptState;
    vector<AcceptState> acceptStates;

    Node* startState;

public:
    unsigned static int nodeCount;
    static vector<Node*> staticNodes;

    static void cleanUpStaticNodes();
    static NFA characterNFA(char transChar);
    static NFA unionedNFA(NFA nfa1, NFA nfa2);
    static NFA concatenatedNFA(NFA nfa1, const NFA& nfa2);
    static NFA kleeneNFA(NFA nfa1);
    // static NFA plusNFA(NFA nfa1);

    static vector<Node*> getTransitionStates(const vector<Node*>& startNodes, char transChar);
    static vector<Node*> getEpsilonTransitionStates(const vector<Node*>& startNodes);

    bool inAnAcceptState(Node* nodeToTest);
    vector<AcceptState> getAcceptStatesIn(vector<Node*> nodesToTest);

    Node* getStartState();
    Node* getAcceptState();

    vector<AcceptState> getAcceptStates();

    void setAcceptStates(vector<AcceptState> acceptStates);

    // Returns the states reachable along epsilon transitions
    vector<Node*> getEpsilonClosure(vector<Node*> startStates);
};

#endif //ENGINEERING_A_COMPILER_NFA_H
