//
// Created by dpmar on 7/28/2022.
//

#include "NFAandRegexUtils/Node.h"
#include "NFAandRegexUtils/ScanHelper.h"
#include "FileHandling/FileReader.h"
#include "TokenAndLexemeUtils/TokenHelper.h"
#include "ParserFuncs/RecursiveDescentParser.h"


int main() {
    FileReader fr;
    auto lexemes = fr.getLexemesFromFile("Scanning/TestInputs/TestLexemes.txt");
//
    auto nfaForLexemes = generateNFAfromLexemes(lexemes);
    auto tokensFromFile = getTokensFromFile(nfaForLexemes,
                                            "Scanning/TestInputs/TestProgram.txt");

    runProgram(tokensFromFile);

    NFA::cleanUpStaticNodes();

    return 0;
}
