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

NFA::~NFA() {
    for (auto node : nodes) {
        std::cout << "Deleting a node with id: " << node->getIdentifier() << std::endl;
        delete node;
    }
}

NFA NFA::characterNFA(char transChar) {
    NFA returnNFA;

    Node* startNode = new Node(nodeCount);
    std::cout << "Creating a node with id: " << startNode->getIdentifier() << std::endl;
    nodeCount++;
    Node* acceptNode = new Node(nodeCount);
    std::cout << "Creating a node with id: " << acceptNode->getIdentifier() << std::endl;
    nodeCount++;

    startNode->addTransitionState(transChar, acceptNode);

//    returnNFA.addNode(startNode);
//    returnNFA.addNode(acceptNode);

    returnNFA.startState = startNode;
    returnNFA.acceptState = acceptNode;

    return returnNFA;
}

NFA NFA::unionedNFA(NFA nfa1, NFA nfa2) {
    NFA unionedNFA;

    Node* newStartState = new Node(nodeCount);
    std::cout << "Creating a node with id: " << newStartState->getIdentifier() << std::endl;
    nodeCount++;
    Node* newAcceptState = new Node(nodeCount);
    std::cout << "Creating a node with id: " << newAcceptState->getIdentifier() << std::endl;
    nodeCount++;

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

NFA NFA::concatenatedNFA(NFA nfa1, NFA nfa2) {
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
    auto newAcceptState = new Node(nodeCount);
    nodeCount++;

    kleenedNFA.addNode(newStartState);
    kleenedNFA.startState = newStartState;

    kleenedNFA.addNode(newAcceptState);
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

// Represents a Kleene closure but requires a minimum of one of the patterns -- simply remove the epsilon transition from
// the start to the accept state
NFA NFA::plusNFA(NFA nfa1) {
    NFA kleenedNFA;

    auto newStartState = new Node(nodeCount);
    nodeCount++;
    auto newAcceptState = new Node(nodeCount);
    nodeCount++;

    kleenedNFA.addNode(newStartState);
    kleenedNFA.startState = newStartState;

    kleenedNFA.addNode(newAcceptState);
    kleenedNFA.acceptState = newAcceptState;

    // kleenedNFA.addNodes(nfa1.nodes);

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

void NFA::addNode(Node* nodeToAdd) {
    // Node* copiedNode = new Node(nodeToAdd->getIdentifier());

    nodes.push_back(nodeToAdd);
}

void NFA::addNodes(const vector<Node*>& nodesToAdd) {
    for(auto node : nodesToAdd) {
        // Node* copiedNode = new Node(node->getIdentifier());

        nodes.push_back(node);
    }
}

vector<Node*> NFA::getTransitionStates(Node* startNode, char transChar) {
    auto transitionsFromStartNode = startNode->getTransitionStates(transChar);
    auto epsilonTransitionsFromStartNode = startNode->getEpsilonTransitionStates();

    for(auto node : epsilonTransitionsFromStartNode) {
        transitionsFromStartNode.push_back(node);
    }

    return transitionsFromStartNode;
}

vector<Node*> NFA::getEpsilonTransitionStates(Node *startNode) {
    auto epsilonTransitionsFromStartNode = startNode->getEpsilonTransitionStates();

    return epsilonTransitionsFromStartNode;
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

unsigned int NFA::getNodeCount() { return nodeCount; }

Node *NFA::getStartState() {
    return startState;
}

Node *NFA::getAcceptState() {
    return acceptState;
}

vector<Node *> NFA::getStates() {
    return nodes;
}

string NFA::getLabel(Node *nodeToFind) {
    for (auto acceptState : acceptStates) {
        if (acceptState.getNode() == nodeToFind) {
            return acceptState.getLabel();
        }
    }

    return "";
}

void NFA::addAcceptState(string label, Node* nodeToAdd) {
    auto newAcceptState = AcceptState(std::move(label), nodeToAdd);
    acceptStates.push_back(newAcceptState);
}

vector<AcceptState> NFA::getAcceptStates() {
    return acceptStates;
}

