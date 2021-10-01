#ifndef PROJECT_1_MLCOMMENTAUTOMATON_H
#define PROJECT_1_MLCOMMENTAUTOMATON_H


#include "Automaton.h"

class MLCommentAutomaton : public Automaton
{
private:
    void S1(const std::string& input);
    void S2(const std::string& input);
    void S3(const std::string& input);

public:
    MLCommentAutomaton() : Automaton(TokenType::COMMENT) {}  // Call the base constructor

    void S0(const std::string& input);
};


#endif //PROJECT_1_MLCOMMENTAUTOMATON_H
