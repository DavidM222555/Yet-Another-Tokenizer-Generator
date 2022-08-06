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
bool StartPrime();
bool Statement();

bool Expr();
bool While();

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
        std::cout << "Tokens left: " << std::endl;

        for (auto token : globalTokens) {
            std::cout << "Token label: " << token.getLexemeForToken().getLabel() << std::endl;
        }

        return true;
    } else {
        std::cout << "Program failed" << std::endl;
        return false;
    }
}


bool Start() {
    while (true) {
        if (globalTokens.empty()) {
            return true;
        }
        else if (Statement()) {
            std::cout << "While was true" << std::endl;
            continue;
        }
        else {

            return false;
        }
    }
}

bool Statement() {
    if (Assignment()) {
        return true;
    }
    else if(While()) {
        if (Statement()) {
            std::cout << "In here" << std::endl;
            return true;
        }
        std::cout << "Out here" << std::endl;
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

bool Assignment() {
    std::cout << "Assignment operator " << std::endl;
    for (auto token : globalTokens) {
        std::cout << token.getLexemeForToken().getLabel() << std::endl;
    }

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

            std::cout << "Here ready to get semicolon" << std::endl;
            std::cout << "Most recent token: " << globalTokens.at(0).getLexemeForToken().getLabel() << std::endl;

            if (globalTokens.at(0).getLexemeForToken().getLabel() == "Semicolon") {
                globalTokens.erase(globalTokens.begin());
                return true;
            }
        }
    }

    return false;
}