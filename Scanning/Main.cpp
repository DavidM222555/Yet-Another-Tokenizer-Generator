//
// Created by dpmar on 7/28/2022.
//

#include "NFAandRegexUtils/Node.h"
#include "NFAandRegexUtils/ScanHelper.h"
#include "FileHandling/FileReader.h"
#include "FileHandling/TokenHelper.h"

#include <iostream>

int main() {
    FileReader fr;

    auto lexemes = fr.getLexemesFromFile("Scanning/TestInputs/TestInput1.txt");
    fr.printLexemes();
    auto nfaForLexemes = generateNFAfromLexemes(lexemes);
    auto tokensFromFile = getTokensFromText(nfaForLexemes, "WHILE [3 <= 4] 3 PLUS 4 PLUS 5 SUB 3; WHILE 4 PLUS 3");

    for (auto token : tokensFromFile) {
        std::cout << "Lexeme: " << token.getLexemeForToken().getLabel() << " with token: " << token.getTokenString() << std::endl;
    }

    NFA::cleanUpStaticNodes();

    return 0;
}
