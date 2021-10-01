#include "StringAutomaton.h"
#include <iostream>

void StringAutomaton::S0(const std::string& input) {
    if (input[index] == '\'') {
        inputRead++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}

void StringAutomaton::S1(const std::string& input) {

    if (input[index] == '\n') {
        newLines++;
    }

    if (index >= input.size()) {
        this->type = TokenType::UNDEFINED;
    }
    else if (input[index] != '\'') {
        inputRead++;
        index++;
        S1(input);
    }
    else if (input[index] == '\'') {
        inputRead++;
        index++;
        S2(input);
    }
}

void StringAutomaton::S2(const std::string& input) {
    if (input[index] == '\'') {
        inputRead++;
        index++;
        S1(input);
    }
}