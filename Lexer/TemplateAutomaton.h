#ifndef PROJECT_1_TEMPLATEAUTOMATON_H
#define PROJECT_1_TEMPLATEAUTOMATON_H

#include "Automaton.h"

class TemplateAutomaton : public Automaton
{
public:
    TemplateAutomaton(TokenType type) : Automaton(type) {}
    void S0(const std::string& input);

private:
    std::string StrToFind();
};


#endif //PROJECT_1_TEMPLATEAUTOMATON_H
