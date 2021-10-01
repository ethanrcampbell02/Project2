#include "TemplateAutomaton.h"

// Returns the desired string to look for in the input which corresponds to the type of the automaton
std::string TemplateAutomaton::StrToFind() {
    switch (type) {
        case TokenType::COMMA:       return ",";
        case TokenType::PERIOD:      return ".";
        case TokenType::Q_MARK:      return "?";
        case TokenType::LEFT_PAREN:  return "(";
        case TokenType::RIGHT_PAREN: return ")";
        case TokenType::MULTIPLY:    return "*";
        case TokenType::ADD:         return "+";
        case TokenType::SCHEMES:     return "Schemes";
        case TokenType::FACTS:       return "Facts";
        case TokenType::RULES:       return "Rules";
        case TokenType::QUERIES:     return "Queries";
        default: return "Error";
    }
}

void TemplateAutomaton::S0(const std::string& input) {
    for (char c : StrToFind()) {
        if (input[index] == c) {
            inputRead++;
            index++;
        }
        else {
            Serr();
            break;
        }
    }

}
