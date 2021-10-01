#include "SLCommentAutomaton.h"

void SLCommentAutomaton::S0(const std::string& input) {
    if (input[index] == '#') {
        inputRead++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}

void SLCommentAutomaton::S1(const std::string& input) {
    if (input[index] != '|') {
        inputRead++;
        index++;
        S2(input);
    }
}

void SLCommentAutomaton::S2(const std::string& input) {
    if (input[index] != '\n' && index < input.size()) {
        inputRead++;
        index++;
        S2(input);
    }
}