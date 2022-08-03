//
// Created by dpmar on 7/28/2022.
//

#ifndef ENGINEERING_A_COMPILER_NFA_H
#define ENGINEERING_A_COMPILER_NFA_H

#include <vector>
#include <string>

#include "Node.h"
#include "NFAandRegexUtils/AcceptState.h"

using std::vector;
using std::string;

class NFA {
private:

    vector<Node*> nodes;
    Node* acceptState;
    vector<AcceptState> acceptStates;

    Node* startState;

public:
    unsigned static int nodeCount;

    ~NFA();

    static NFA characterNFA(char transChar);
    static NFA unionedNFA(NFA nfa1, NFA nfa2);
    static NFA concatenatedNFA(NFA nfa1, NFA nfa2);
    static NFA kleeneNFA(NFA nfa1);
    static NFA plusNFA(NFA nfa1);

    void addNode(Node* nodeToAdd);
    void addNodes(const vector<Node*>& nodesToAdd);

    static vector<Node*> getTransitionStates(Node* startNode, char transChar);
    static vector<Node*> getTransitionStates(const vector<Node*>& startNodes, char transChar);

    static vector<Node*> getEpsilonTransitionStates(Node* startNode);
    static vector<Node*> getEpsilonTransitionStates(const vector<Node*>& startNodes);

    vector<Node*> getStates();

    Node* getStartState();
    Node* getAcceptState();

    static unsigned int getNodeCount();

    string getLabel(Node* nodeToFind);

    void addAcceptState(string label, Node* nodeToAdd);
    vector<AcceptState> getAcceptStates();


};

#endif //ENGINEERING_A_COMPILER_NFA_H
