cmake_minimum_required(VERSION 3.17)
project(Interpreter)

set(CMAKE_CXX_STANDARD 14)

include_directories(Lexer)
include_directories(Parser)

add_executable(Interpreter
        main.cpp
        Lexer/Automaton.h
        Lexer/ColonAutomaton.cpp
        Lexer/ColonAutomaton.h
        Lexer/ColonDashAutomaton.cpp
        Lexer/ColonDashAutomaton.h
        Lexer/IdentifierAutomaton.cpp
        Lexer/IdentifierAutomaton.h
        Lexer/Lexer.cpp
        Lexer/Lexer.h
        Lexer/MLCommentAutomaton.cpp
        Lexer/MLCommentAutomaton.h
        Lexer/SLCommentAutomaton.cpp
        Lexer/SLCommentAutomaton.h
        Lexer/StringAutomaton.cpp
        Lexer/StringAutomaton.h
        Lexer/TemplateAutomaton.cpp
        Lexer/TemplateAutomaton.h
        Lexer/Token.cpp
        Lexer/Token.h
        Parser/Parser.cpp
        Parser/Parser.h
        Parser/DatalogProgram.cpp
        Parser/DatalogProgram.h
        Parser/Rule.cpp Parser/Rule.h
        Parser/Predicate.cpp
        Parser/Predicate.h
        Parser/Parameter.cpp
        Parser/Parameter.h)
