//
// Created by dpmar on 8/3/2022.
//

#ifndef ENGINEERING_A_COMPILER_TOKENHELPER_H
#define ENGINEERING_A_COMPILER_TOKENHELPER_H

#include <vector>
#include <algorithm>

#include "TokenAndLexemeUtils/Token.h"
#include "NFAandRegexUtils/NFA.h"

using std::vector;
using std::find;

/*
 * Scans through a given string with nfaForTokenization and returns a vector of tokens within that text
 */
vector<Token> getTokensFromText(NFA nfaForTokenization, string stringToScan) {
    vector<Token> returnTokens;

    auto startNode = nfaForTokenization.getStartState();
    auto epsilonStates = startNode->getEpsilonTransitionStates();

    // Keep track of our current states
    vector<Node*> currentStates;

    // Push the start node to the current states
    currentStates.push_back(startNode);

    Token mostRecentToken;
    string currentString;

    auto prevStateSize = currentStates.size();

    for (auto i = 0; i < stringToScan.size(); i++) {
        auto ch = stringToScan[i];

        // Ignore whitespace in the program
        if (ch == ' ') {
            continue;
        }

        currentString += ch;

        // Begin by getting all states reachable along initial epsilon transitions
        currentStates = nfaForTokenization.getEpsilonClosure(currentStates);

        // Next get all transition states along the current character that we are reading
        auto charTransStates = NFA::getTransitionStates(currentStates, ch);

        // Add all the states reachable by ch
        for (auto node : charTransStates) {
            currentStates.push_back(node);
        }

        // First get the transition states reachable along a given character and then
        // from there go along all epsilon states.
        currentStates = NFA::getTransitionStates(currentStates, ch);
        currentStates = nfaForTokenization.getEpsilonClosure(currentStates);

        // Get all accept states we are currently in
        auto acceptStatesIn = nfaForTokenization.getAcceptStatesIn(currentStates);

        if (!acceptStatesIn.empty()) {
            for (auto acceptState : acceptStatesIn) {
                mostRecentToken = Token(acceptState.getLexeme(), currentString);
            }
        }

        if (prevStateSize == 0 && currentStates.empty()) {
            std::cout << "Parse error at index = " << i << std::endl;
            break;
        }

        prevStateSize = currentStates.size();

        // If the accept states we are in is empty then we print out the token we got along with
        // resetting the current states to the start node. We also reset the possible token string
        if (currentStates.empty()) {

            returnTokens.push_back(mostRecentToken);
            currentStates = {startNode};
            currentString = "";
            i--;
        }

        if (i == stringToScan.size() - 1 && !acceptStatesIn.empty()) {
            returnTokens.push_back(mostRecentToken);
        }
    }

    return returnTokens;
}

#endif //ENGINEERING_A_COMPILER_TOKENHELPER_H
