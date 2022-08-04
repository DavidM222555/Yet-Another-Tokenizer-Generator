//
// Created by dpmar on 8/3/2022.
//

#ifndef ENGINEERING_A_COMPILER_TOKENHELPER_H
#define ENGINEERING_A_COMPILER_TOKENHELPER_H

#include <vector>
#include <algorithm>

#include "Token.h"
#include "NFAandRegexUtils/NFA.h"

using std::vector;
using std::find;

vector<Token> getTokensFromText(NFA nfaForTokenization, string stringToScan) {
    auto startNode = nfaForTokenization.getStartState();
    auto epsilonStates = startNode->getEpsilonTransitionStates();

    // Keep track of our current states
    vector<Node*> currentStates;

    // Push the start node to the current states
    currentStates.push_back(startNode);

    for (auto &ch : stringToScan) {
        while (true) {
            unsigned long long currentNumberOfStates = currentStates.size();

            for (std::vector<Node*>::size_type i = 0; i < currentNumberOfStates; i++) {
                auto currentNode = currentStates[i];

                for (auto epsilonReachableNode : currentNode->getEpsilonTransitionStates()) {
                    if (std::find(currentStates.begin(), currentStates.end(), epsilonReachableNode) == currentStates.end()) {
                        currentStates.push_back(epsilonReachableNode);
                    }
                }
            }

            if(currentNumberOfStates == currentStates.size()) {
                break;
            }
        }

        auto charTransStates = NFA::getTransitionStates(currentStates, ch);

        for (auto node : charTransStates) {
            currentStates.push_back(node);
        }

        currentStates = NFA::getTransitionStates(currentStates, ch);

        auto epsilonStatesFromCurrentStates = NFA::getEpsilonTransitionStates(currentStates);

        while (true) {
            unsigned long long currentNumberOfStates = currentStates.size();

            for (std::vector<Node*>::size_type i = 0; i < currentNumberOfStates; i++) {
                auto currentNode = currentStates[i];

                for (auto epsilonReachableNode : currentNode->getEpsilonTransitionStates()) {
                    if (std::find(currentStates.begin(), currentStates.end(), epsilonReachableNode) == currentStates.end()) {
                        currentStates.push_back(epsilonReachableNode);
                    }
                }
            }

            if(currentNumberOfStates == currentStates.size()) {
                break;
            }
        }

        for (auto state : currentStates) {
            std::cout << state->getIdentifier() << std::endl;
        }

    }
}

#endif //ENGINEERING_A_COMPILER_TOKENHELPER_H
