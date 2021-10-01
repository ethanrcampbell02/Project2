#ifndef PROJECT_1_IDENTIFIERAUTOMATON_H
#define PROJECT_1_IDENTIFIERAUTOMATON_H


#include "Automaton.h"

class IdentifierAutomaton : public Automaton
{
private:
    void S1(const std::string& input);

public:
    IdentifierAutomaton() : Automaton(TokenType::ID) {}  // Call the base constructor

    void S0(const std::string& input);
};

#endif //PROJECT_1_IDENTIFIERAUTOMATON_H
