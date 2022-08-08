//
// Created by dpmar on 7/29/2022.
//

#include "NFAandRegexUtils/NFA.h"
#include "TokenAndLexemeUtils/Lexeme.h"

#include <string>
#include <iostream>
#include <unordered_set>
#include <algorithm>
#include <unordered_map>
#include <stack>
#include <queue>

#pragma clang diagnostic push
#pragma ide diagnostic ignored "LocalValueEscapesScope"
using std::string;
using std::unordered_set;
using std::find;

std::unordered_map<char, int> precedenceMap = {
        {'*', 3},
        {'.', 2},
        {'|', 1},
        {'(', 0},
        {')', 0}
};

// Simulates an NFA on a given string and outputs whether the NFA ends in an accept state
bool scanString(NFA scannerNFA, const string& stringToScan) {
    auto startNode = scannerNFA.getStartState();
    auto epsilonStates = startNode->getEpsilonTransitionStates();

    // Keep track of our current states
    vector<Node*> currentStates;

    // Push the start node to the current states
    currentStates.push_back(startNode);

    for (auto &ch : stringToScan) {
        currentStates = scannerNFA.getEpsilonClosure(currentStates);

        auto charTransStates = NFA::getTransitionStates(currentStates, ch);

        for (auto node : charTransStates) {
            currentStates.push_back(node);
        }

        currentStates = NFA::getTransitionStates(currentStates, ch);

        currentStates = scannerNFA.getEpsilonClosure(currentStates);
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

// This makes concatenation explicit for stringToConvert -- for instance 'ab' is translated to 'a.b'
string addConcatOperators(string stringToConvert) {
    string returnString;

    remove(stringToConvert.begin(), stringToConvert.end(), ' ');

    for (auto i = 0; i < stringToConvert.size(); i++) {
        if(i + 1 < stringToConvert.size()) {
            bool leftCharFlag = !isOperator(stringToConvert[i]) || stringToConvert[i] == ')'
                    || stringToConvert[i] == '*';

            bool letterOrDigitFlag = !isOperator(stringToConvert[i + 1]);
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

// Shunting-Yard algorithm below here
string convertToPostfix(const string& regex) {
    std::queue<char> outputQueue;
    std::stack<char> operatorStack;

    for (auto i = 0; i < regex.size(); i++) {
        auto ch = regex[i];

        if (ch == '(') {
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
        else {
            outputQueue.push(ch);
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


// Generates an NFA from a regex by first converting the regex to postfix and then building a stack
// from the NFAs represented by working through the postfix regex.
// Consider the simple regex ab. (which is in postfix notation).
// It works from right to left, first making a character NFA for a, then a character NFA for b, and then when it
// encounters '.', which is the operator for concatenation, it pops two NFAs off the stack and creates a concat NFA
// for those two items. For the unary Kleene operator it simply just pops the top element, performs the transformation,
// and then pushes back to the stack.
NFA generateNFAFromRegex(string regex) {
    NFA regexNFA;
    std::stack<NFA> nfaStack;

    // First add concatenation operator and then convert to postfix
    regex = addConcatOperators(regex);
    regex = convertToPostfix(regex);

    for (auto i = 0; i < regex.size(); i++) {
        auto ch = regex[i];

        if (!isOperator(ch)) {
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
            } else if (ch == '|') {
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


// Takes in a list of lexemes and produces the NFA for recognizing any regex corresponding to any lexeme.
NFA generateNFAfromLexemes(vector<Lexeme> listOfLexemes) {
    NFA returnNFA;
    vector<AcceptState> acceptStates;

    // We have to begin by getting the first lexeme and giving our returnNFA an initial value that we will
    // use to union with the other NFAs
    if (!listOfLexemes.empty()) {
        auto regex = listOfLexemes[0].getRegex();
        returnNFA = generateNFAFromRegex(regex);

        auto acceptState = AcceptState(listOfLexemes[0], returnNFA.getAcceptState());
        acceptStates.push_back(acceptState);
    }

    // Iterate through the other lexemes and progressively union them into our returnNFA
    for (int i = 1; i < listOfLexemes.size(); i++) {
        auto regex = listOfLexemes[i].getRegex();
        auto nfaToUnionWith = generateNFAFromRegex(regex);

        returnNFA = NFA::unionedNFA(returnNFA, nfaToUnionWith);

        // We need to keep track of what the accept state of this NFA was so we can use it for tokenizing later
        auto acceptState = AcceptState(listOfLexemes[i], nfaToUnionWith.getAcceptState());
        acceptStates.push_back(acceptState);
    }

    returnNFA.setAcceptStates(acceptStates);

    return returnNFA;
}

#pragma clang diagnostic pop