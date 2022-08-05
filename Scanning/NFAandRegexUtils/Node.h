//
// Created by dpmar on 7/28/2022.
//

#include <vector>
#include <unordered_map>

using std::vector;
using std::unordered_map;

#ifndef ENGINEERING_A_COMPILER_NODE_H
#define ENGINEERING_A_COMPILER_NODE_H

class Node {
private:
    unordered_map<char, vector<Node*>> transitionStates;
    vector<Node*> epsilonTransitions;
    unsigned int identifier;

public:
    Node(unsigned int identifier);

    // Add a transition state from one node to another along a given transition character
    void addTransitionState(char transChar, Node* transitionState);
    vector<Node*> getTransitionStates(char transChar);

    // Add an epsilon transition from one state to another -- these are states
    // that are always reachable from another no matter the current character being scanned
    void addEpsilonTransition(Node* transitionState);
    vector<Node*> getEpsilonTransitionStates();

    unsigned int getIdentifier() const;
};

#endif //ENGINEERING_A_COMPILER_NODE_H
