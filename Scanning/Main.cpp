//
// Created by dpmar on 7/28/2022.
//

#include "NFAandRegexUtils/Node.h"
#include "NFAandRegexUtils/NFA.h"
#include "NFAandRegexUtils/ScanHelper.h"
#include "FileHandling/FileReader.h"

int main() {

    NFA nfa = generateNFAFromRegex("(a+b)*cde*");

    std::cout << scanString(nfa, "abbbbbcdee") << std::endl;

    NFA::cleanUpStaticNodes();

    return 0;
}
