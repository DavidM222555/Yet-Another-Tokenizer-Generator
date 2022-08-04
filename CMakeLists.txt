cmake_minimum_required(VERSION 3.18)
project(Engineering_a_Compiler)

set(CMAKE_CXX_STANDARD 14)

include_directories(Scanning)

add_executable(Engineering_a_Compiler
        Scanning/Main.cpp
        Scanning/NFAandRegexUtils/Node.cpp
        Scanning/NFAandRegexUtils/Node.h
        Scanning/NFAandRegexUtils/NFA.cpp
        Scanning/NFAandRegexUtils/NFA.h
        Scanning/NFAandRegexUtils/ScanHelper.h
        Scanning/NFAandRegexUtils/AcceptState.h
        Scanning/FileHandling/FileReader.cpp Scanning/FileHandling/FileReader.h
        Scanning/FileHandling/Lexeme.h Scanning/FileHandling/Token.h Scanning/FileHandling/TokenHelper.h)
