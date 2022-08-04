//
// Created by dpmar on 7/28/2022.
//

#include "NFAandRegexUtils/Node.h"
#include "NFAandRegexUtils/ScanHelper.h"
#include "FileHandling/FileReader.h"
#include "FileHandling/TokenHelper.h"

int main() {
    FileReader fr;

    auto lexemes = fr.getLexemesFromFile("Scanning/TestInputs/TestInput1.txt");
    fr.printLexemes();
    auto nfaForLexemes = generateNFAfromLexemes(lexemes);
    std::cout << "Result: " << scanString(nfaForLexemes, "ccccccccc") << std::endl;

    getTokensFromText(nfaForLexemes, "blehhhh");

    NFA::cleanUpStaticNodes();


    return 0;
}
