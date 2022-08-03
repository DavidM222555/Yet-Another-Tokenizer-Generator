//
// Created by dpmar on 7/28/2022.
//

#include <iostream>
#include "NFAandRegexUtils/Node.h"
#include "NFAandRegexUtils/NFA.h"
#include "NFAandRegexUtils/ScanHelper.h"
#include "FileHandling/FileReader.h"


int main() {

    NFA nfa = generateNFAFromRegex("(abc)*cde(fg)*");
    NFA aNFA = NFA::characterNFA('a');

    return 0;
}
