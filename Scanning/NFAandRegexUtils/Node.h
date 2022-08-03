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

    void addTransitionState(char transChar, Node* transitionState);
    vector<Node*> getTransitionStates(char transChar);

    void addEpsilonTransition(Node* transitionState);
    vector<Node*> getEpsilonTransitionStates();

    void setIdentifier(unsigned int newId);
    unsigned int getIdentifier() const;
};

#endif //ENGINEERING_A_COMPILER_NODE_H
