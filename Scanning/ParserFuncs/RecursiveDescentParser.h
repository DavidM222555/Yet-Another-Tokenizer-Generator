//
// Created by dpmar on 8/5/2022.
//

#include <vector>
using std::vector;

#include <iostream>
#include <algorithm>
using std::reverse;

#include <TokenAndLexemeUtils/Token.h>

vector<Token> globalTokens;

bool Start();
bool Statement();

bool While();
bool EndWhile();

bool If();

bool BoolExpr();
bool BoolExprPrime();
bool BoolVal();
bool BoolOp();

bool ArithExpr();
bool ArithExprPrime();
bool ArithOp();
bool ArithVal();

bool Assignment();
bool IfStatement();


bool runProgram(vector<Token>& tokens) {
    globalTokens = tokens;

    if (Start()) {
        std::cout << "Program terminated successfully" << std::endl;

        return true;
    } else {
        std::cout << "Program failed" << std::endl;
        return false;
    }
}


bool Start() {
    while (true) {

        if (globalTokens.empty()) {
            std::cout << "Here in returning true hopefully " << std::endl;
            return true;
        }
        else if (Statement()) {
            continue;
        }
        else {
            return false;
        }
    }
}

bool StatementList() {
    if (Statement()) {
        return StatementList();
    }

    return true;
}

bool Statement() {
    if (Assignment()) {
        return true;
    }
    else if (While()) {
        if(StatementList()) {
            if (EndWhile()) {
                return true;
            }
        }
    }
    else if (If()) {
        return true;
    }

    return false;
}


bool While() {
    if (globalTokens.size() < 2) {
        return false;
    }

    auto firstWordLabel = globalTokens.at(0).getLexemeForToken().getLabel();
    auto secondWordLabel = globalTokens.at(1).getLexemeForToken().getLabel();

    if (firstWordLabel == "While" && secondWordLabel == "LBracket") {
        globalTokens.erase(globalTokens.begin());
        globalTokens.erase(globalTokens.begin());

        if (BoolExpr()) {
            if (globalTokens.size() < 2) {
                std::cout << "Failed with less than enough tokens " << std::endl;
                return false;
            }

            auto possibleRightBracket = globalTokens.at(0).getLexemeForToken().getLabel();
            auto possibleColon = globalTokens.at(1).getLexemeForToken().getLabel();

            if (possibleRightBracket == "RBracket" && possibleColon == "Colon") {
                globalTokens.erase(globalTokens.begin());
                globalTokens.erase(globalTokens.begin());

                return true;
            }
        }
    }

    return false;
}


bool BoolExpr() {
    if (BoolVal() && BoolExprPrime()) {
        return true;
    }

    return false;
}

bool BoolExprPrime() {
    if (BoolOp()) {
        if (BoolExpr()) {
            if (BoolExprPrime()) {
                return true;
            }
        }
        return false;
    }

    return true;
}

bool BoolVal() {
    if (globalTokens.empty()) {
        return false;
    }

    auto expectedBoolean = globalTokens.at(0).getLexemeForToken().getLabel();

    if (expectedBoolean == "True" || expectedBoolean == "False") {
        globalTokens.erase(globalTokens.begin());
        return true;
    }

    return false;
}

bool BoolOp() {
    if (globalTokens.empty()) {
        return false;
    }

    auto expectedOp = globalTokens.at(0).getLexemeForToken().getLabel();

    if (expectedOp == "And" || expectedOp == "Or" || expectedOp == "Not"
    || expectedOp == "Xor") {
        globalTokens.erase(globalTokens.begin());
        return true;
    }

    return false;
}

bool ArithExpr() {
    if (ArithVal() && ArithExprPrime()) {
        return true;
    }

    return false;
}

bool ArithExprPrime() {
    if (ArithOp()) {
        if (ArithExpr()) {
            if (ArithExprPrime()) {
                return true;
            }
        }
        return false;
    }

    return true;
}

bool ArithVal() {
    if (globalTokens.empty()) {
        return false;
    }

    auto expectedNumber = globalTokens.at(0).getLexemeForToken().getLabel();

    if (expectedNumber == "Number") {
        globalTokens.erase(globalTokens.begin());
        return true;
    }

    return false;
}

bool EndWhile() {
    if (globalTokens.size() < 2) {
        return false;
    }

    auto expectedEnd = globalTokens.at(0).getLexemeForToken().getLabel();
    auto expectedWhile = globalTokens.at(1).getLexemeForToken().getLabel();

    if (expectedEnd == "End" && expectedWhile == "While") {
        globalTokens.erase(globalTokens.begin());
        globalTokens.erase(globalTokens.begin());

        return true;
    }

    return false;
}

bool ArithOp() {
    if (globalTokens.empty()) {
        return false;
    }

    auto expectedOp = globalTokens.at(0).getLexemeForToken().getLabel();

    if (expectedOp == "Plus" || expectedOp == "Subtract" || expectedOp == "Divide"
        || expectedOp == "Modulus") {
        globalTokens.erase(globalTokens.begin());
        return true;
    }

    return false;
}

bool If() {
    if (globalTokens.size() < 2) {
        return false;
    }

    auto expectedIf = globalTokens.at(0).getLexemeForToken().getLabel();
    auto expectedLeftBracket = globalTokens.at(1).getLexemeForToken().getLabel();

    if (expectedIf == "If" && expectedLeftBracket == "LBracket") {

        globalTokens.erase(globalTokens.begin());
        globalTokens.erase(globalTokens.begin());

        if (BoolExpr()) {
            if(globalTokens.size() <2) {
                return false;
            }

            auto rightBracket = globalTokens.at(0).getLexemeForToken().getLabel();
            auto expectedColon = globalTokens.at(1).getLexemeForToken().getLabel();

            if (rightBracket == "RBracket" && expectedColon == "Colon") {

                globalTokens.erase(globalTokens.begin());
                globalTokens.erase(globalTokens.begin());

                if (StatementList()) {
                    if (globalTokens.size() < 2) {
                        return false;
                    }

                    auto eitherEndOrElse = globalTokens.at(0).getLexemeForToken().getLabel();

                    if (eitherEndOrElse == "End") {
                        globalTokens.erase(globalTokens.begin());

                        auto possibleIf = globalTokens.at(0).getLexemeForToken().getLabel();

                        if (possibleIf == "If") {
                            globalTokens.erase(globalTokens.begin());
                            return true;
                        }
                    }
                }
            }
        }
    }

    return false;
}

bool Assignment() {
    if (globalTokens.size() < 3) {
        return false;
    }

    auto expectedVar = globalTokens.at(0).getLexemeForToken().getLabel();
    auto expectedId = globalTokens.at(1).getLexemeForToken().getLabel();
    auto expectedEq = globalTokens.at(2).getLexemeForToken().getLabel();

    if (expectedVar == "Var" && expectedId == "VariableName" && expectedEq == "Equal") {

        globalTokens.erase(globalTokens.begin());
        globalTokens.erase(globalTokens.begin());
        globalTokens.erase(globalTokens.begin());

        if (ArithExpr() || BoolExpr()) {

            if (globalTokens.empty()) {
                return false;
            }

            if (globalTokens.at(0).getLexemeForToken().getLabel() == "Semicolon") {
                globalTokens.erase(globalTokens.begin());
                return true;
            }
        }
    }

    return false;
}