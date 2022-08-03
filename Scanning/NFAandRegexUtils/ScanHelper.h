//
// Created by dpmar on 7/29/2022.
//

#include "NFAandRegexUtils/NFA.h"

#include <string>
#include <iostream>
#include <unordered_set>
#include <algorithm>
#include <unordered_map>
#include <stack>
#include <queue>

using std::string;
using std::unordered_set;
using std::find;

std::unordered_map<char, int> precedenceMap = {
        {'*', 3},
        {'.', 2},
        {'+', 1},
        {'(', 0},
        {')', 0}
};

bool scanString(NFA scannerNFA, const string& stringToScan) {
    auto startNode = scannerNFA.getStartState();
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

    }

    for (auto node : currentStates) {
        if(node == scannerNFA.getAcceptState()) {
            return true;
        }
    }

    return false;
}

bool isOperator(char opToTest) {
    return precedenceMap.find(opToTest) != precedenceMap.end();
}

// This makes concatenation explicit for stringToConvert
string addConcatOperators(string stringToConvert) {
    string returnString;

    remove(stringToConvert.begin(), stringToConvert.end(), ' ');

    for (auto i = 0; i < stringToConvert.size(); i++) {
        if(i + 1 < stringToConvert.size()) {
            bool leftCharFlag = isalnum(stringToConvert[i]) || stringToConvert[i] == ')'
                    || stringToConvert[i] == '*';

            bool letterOrDigitFlag = isalnum(stringToConvert[i + 1]);
            bool rightCharFlag = letterOrDigitFlag || (stringToConvert[i + 1] == '(');

            if(leftCharFlag && rightCharFlag) {
                returnString += (stringToConvert[i]);
                returnString += ".";
            } else {
                returnString += stringToConvert[i];
            }
        }
    }

    returnString += stringToConvert[stringToConvert.size() - 1];

    return returnString;
}

string convertToPostfix(const string& regex) {

    std::queue<char> outputQueue;
    std::stack<char> operatorStack;


    for (auto &ch : regex) {
        if (isalnum(ch)) {
            outputQueue.push(ch);
        }
        else if (ch == '(') {
            operatorStack.push(ch);
        }
        else if (ch == ')') {
            while(!operatorStack.empty() && operatorStack.top() != '(') {
                outputQueue.push(operatorStack.top());
                operatorStack.pop();
            }

            operatorStack.pop();
        }
        else if (isOperator(ch) && !operatorStack.empty() && operatorStack.top() == '(') {
            operatorStack.push(ch);
        }
        else if(isOperator(ch)) {
            if(operatorStack.empty()) {
                operatorStack.push(ch);
                continue;
            }

            while(!operatorStack.empty()) {
                if (precedenceMap.at(operatorStack.top()) > precedenceMap.at(ch)) {
                    outputQueue.push(operatorStack.top());
                    operatorStack.pop();
                } else {
                    operatorStack.push(ch);
                    break;
                }
            }

            if(operatorStack.empty()) {
                operatorStack.push(ch);
            }
        }
    }

    while(!operatorStack.empty()) {
        outputQueue.push(operatorStack.top());
        operatorStack.pop();
    }

    string returnString;

    while(!outputQueue.empty()) {
        returnString += outputQueue.front();
        outputQueue.pop();
    }

    return returnString;
}

NFA generateNFAFromRegex(string regex) {
    NFA regexNFA;
    std::stack<NFA> nfaStack;

    // First add concatenation operator and then convert to postfix
    regex = addConcatOperators(regex);
    regex = convertToPostfix(regex);

    std::cout << "Regex string: " << regex << std::endl;

    for (auto& ch : regex) {
        if (isalnum(ch)) {
            NFA charNFA = NFA::characterNFA(ch);
            nfaStack.push(charNFA);
        }
        else if (isOperator(ch)) {
            if(ch == '*') {
                NFA topNFA = nfaStack.top();
                nfaStack.pop();

                NFA kleeneNFA = NFA::kleeneNFA(topNFA);
                nfaStack.push(kleeneNFA);
            } else if (ch == '.') {
                NFA concatNFA1 = nfaStack.top();
                nfaStack.pop();
                NFA concatNFA2 = nfaStack.top();
                nfaStack.pop();

                NFA concatenatedNFA = NFA::concatenatedNFA(concatNFA2, concatNFA1);
                nfaStack.push(concatenatedNFA);
            } else if (ch == '+') {
                NFA unionedNFA1 = nfaStack.top();
                nfaStack.pop();
                NFA unionedNFA2 = nfaStack.top();
                nfaStack.pop();

                NFA unionedNFA = NFA::unionedNFA(unionedNFA2, unionedNFA1);
                nfaStack.push(unionedNFA);
            }
        }
    }

    return nfaStack.top();
}
