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
    auto lexemes = fr.getLexemesFromFile("Scanning/TestInputs/TestInput1.txt");

    auto nfaForLexemes = generateNFAfromLexemes(lexemes);
    auto tokensFromFile = getTokensFromText(nfaForLexemes, "VAR X = 33 PLUS 44; WHILE [TRUE AND FALSE]: VAR Y = 33;");

    runProgram(tokensFromFile);

    NFA::cleanUpStaticNodes();

    return 0;
}
