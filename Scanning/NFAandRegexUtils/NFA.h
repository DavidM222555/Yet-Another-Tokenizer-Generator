//
// Created by dpmar on 7/28/2022.
//

#ifndef ENGINEERING_A_COMPILER_NFA_H
#define ENGINEERING_A_COMPILER_NFA_H

#include <vector>
#include <string>

#include "Node.h"
#include "NFAandRegexUtils/AcceptState.h"
#include "TokenAndLexemeUtils/Lexeme.h"

using std::vector;
using std::string;

class NFA {
private:
    Node* acceptState;
    vector<AcceptState> acceptStates;

    Node* startState;

public:
    unsigned static int nodeCount;

    // Used for memory management due to the fact nodes are constantly reused in different NFAs (more memory-efficient)
    static vector<Node*> staticNodes;

    // Clean up function that should be called immediately before the program ends or all NFA use is completed.
    // This is handle final cleanup of all nodes that have existed and been reused throughout the program
    static void cleanUpStaticNodes();

    // Creates an NFA based off a single character. Has the simple form of a start state, a character transition, and
    // and accept state.
    static NFA characterNFA(char transChar);

    // Creates the union (or alternation) between nfa1 and nfa2.
    static NFA unionedNFA(NFA nfa1, NFA nfa2);

    // Creates the concatenation of nfa1 and nfa2. Has the simple form of creating an epsilon transition from
    // nfa1's accept state to nfa2's start state.
    static NFA concatenatedNFA(NFA nfa1, const NFA& nfa2);

    // Creates the Kleene starred NFA of nfa1. Effectively this allows the pattern represented by nfa1 to be
    // repeated as many times as needed.
    static NFA kleeneNFA(NFA nfa1);

    static vector<Node*> getTransitionStates(const vector<Node*>& startNodes, char transChar);
    static vector<Node*> getEpsilonTransitionStates(const vector<Node*>& startNodes);

    // Tests whether or not a given node is in an accept state of the NFA. This is used for tokenization when
    // we want to determine what lexeme a token fits into (or whether we have an error when we have no lexeme matching).
    bool inAnAcceptState(Node* nodeToTest);

    // Function that returns all accept states we are currently in -- can be used for finding which lexeme has
    // the highest precedence and should be chosen for a given token.
    vector<AcceptState> getAcceptStatesIn(vector<Node*> nodesToTest);

    Node* getStartState();
    Node* getAcceptState();

    void setAcceptStates(vector<AcceptState> acceptStates);

    // Returns the states reachable along epsilon transitions
    vector<Node*> getEpsilonClosure(vector<Node*> startStates);
};

#endif //ENGINEERING_A_COMPILER_NFA_H
