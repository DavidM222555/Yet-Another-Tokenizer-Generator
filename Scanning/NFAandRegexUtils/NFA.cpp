//
// Created by dpmar on 7/28/2022.
//

#include "NFAandRegexUtils/NFA.h"
#include <iostream>
#include <algorithm>
#include <utility>

using std::cout;
using std::find;

unsigned int NFA::nodeCount = 0;
vector<Node*> NFA::staticNodes;

void NFA::cleanUpStaticNodes() {
    for (auto node : staticNodes) {
        delete node;
    }

    std::cout << "Successfully deleted all nodes\n";
}

NFA NFA::characterNFA(char transChar) {
    NFA returnNFA;

    Node* startNode = new Node(nodeCount);
    nodeCount++;
    staticNodes.push_back(startNode);

    Node* acceptNode = new Node(nodeCount);
    nodeCount++;
    staticNodes.push_back(acceptNode);

    startNode->addTransitionState(transChar, acceptNode);

    returnNFA.startState = startNode;
    returnNFA.acceptState = acceptNode;

    return returnNFA;
}


NFA NFA::unionedNFA(NFA nfa1, NFA nfa2) {
    NFA unionedNFA;

    Node* newStartState = new Node(nodeCount);
    nodeCount++;
    staticNodes.push_back(newStartState);

    Node* newAcceptState = new Node(nodeCount);
    nodeCount++;
    staticNodes.push_back(newAcceptState);

    unionedNFA.startState = newStartState;
    unionedNFA.acceptState = newAcceptState;

    // Connect the new start state to the start states of nfa1 and nfa2
    newStartState->addEpsilonTransition(nfa1.getStartState());
    newStartState->addEpsilonTransition(nfa2.getStartState());

    // Connect the old accept states to the new accept state
    nfa1.getAcceptState()->addEpsilonTransition(newAcceptState);
    nfa2.getAcceptState()->addEpsilonTransition(newAcceptState);

    return unionedNFA;
}

NFA NFA::concatenatedNFA(NFA nfa1, const NFA& nfa2) {
    NFA concatenatedNFA;

    // Set the start state to the start state of nfa1
    concatenatedNFA.startState = nfa1.startState;

    // Set the accept state to the accept state of nfa2
    concatenatedNFA.acceptState = nfa2.acceptState;

    // Connect the accept state of nfa1 to the start state of nfa2
    // per Thompson's construction
    nfa1.acceptState->addEpsilonTransition(nfa2.startState);

    return concatenatedNFA;
}


NFA NFA::kleeneNFA(NFA nfa1) {
    NFA kleenedNFA;

    auto newStartState = new Node(nodeCount);
    nodeCount++;
    staticNodes.push_back(newStartState);

    auto newAcceptState = new Node(nodeCount);
    nodeCount++;
    staticNodes.push_back(newAcceptState);

    kleenedNFA.startState = newStartState;
    kleenedNFA.acceptState = newAcceptState;

    // Add an epsilon transition from the start state to
    // the start state of nfa1
    newStartState->addEpsilonTransition(nfa1.startState);

    // Add an epsilon transition from the new start state to the new
    // accept state
    newStartState->addEpsilonTransition(kleenedNFA.acceptState);

    // Add an epsilon transition from the old accept state to
    // the new accept state
    nfa1.acceptState->addEpsilonTransition(kleenedNFA.acceptState);

    // Add an epsilon transition from nfa1's accept state to its
    // start state
    nfa1.acceptState->addEpsilonTransition(nfa1.startState);

    return kleenedNFA;
}



vector<Node*> NFA::getEpsilonTransitionStates(const vector<Node*>& startNodes) {
    vector<Node*> returnVector;

    for(auto node : startNodes) {
        auto transStates = node->getEpsilonTransitionStates();

        for(auto transNode : transStates) {

            if (std::find(returnVector.begin(), returnVector.end(), transNode) == returnVector.end()) {
                returnVector.push_back(transNode);
            }
        }
    }

    return returnVector;
}

vector<Node*> NFA::getTransitionStates(const vector<Node*>& startNodes, char transChar) {
    vector<Node*> returnVector;

    for(auto node : startNodes) {
        auto transStates = node->getTransitionStates(transChar);

        for(auto transNode : transStates) {

            if (std::find(returnVector.begin(), returnVector.end(), transNode) == returnVector.end()) {
                returnVector.push_back(transNode);
            }
        }

    }

    return returnVector;
}


Node *NFA::getStartState() {
    return startState;
}

Node *NFA::getAcceptState() {
    return acceptState;
}


void NFA::setAcceptStates(vector<AcceptState> fAcceptStates) {
    acceptStates = std::move(fAcceptStates);
}

