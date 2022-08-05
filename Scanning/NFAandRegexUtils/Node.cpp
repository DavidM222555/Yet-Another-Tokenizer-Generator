//
// Created by dpmar on 7/28/2022.
//

#include "Node.h"

Node::Node(unsigned int identifier) {
    this->identifier = identifier;
}

void Node::addTransitionState(char transChar, Node *transitionState) {

    // If we haven't encountered a transition along this character yet
    // then we have to initialize it in our map
    if(transitionStates.count(transChar) == 0) {
        vector<Node *> newStates;
        newStates.push_back(transitionState);

        this->transitionStates.insert(std::make_pair(transChar, newStates));

        return;
    }

    // Otherwise we just append at the value vector for that character
    transitionStates.at(transChar).push_back(transitionState);
}

vector<Node*> Node::getTransitionStates(char transChar) {
    if(transitionStates.count(transChar) > 0) {
        return transitionStates.at(transChar);
    }

    return {};
}

unsigned int Node::getIdentifier() const {
    return this->identifier;
}

void Node::addEpsilonTransition(Node *transitionState) {
    this->epsilonTransitions.push_back(transitionState);
}

vector<Node*> Node::getEpsilonTransitionStates() {
    return this->epsilonTransitions;
}
