#ifndef INTERPRETER_PARSER_H
#define INTERPRETER_PARSER_H

#include "Token.h"
#include "DatalogProgram.h"
#include <vector>

class Parser {
private:
    DatalogProgram* ParseDatalogProgram();
    void ParseSchemeList();
    void ParseFactList();
    void ParseRuleList();
    void ParseQueryList();
    Predicate* ParseScheme();
    Predicate* ParseFact();
    Rule* ParseRule();
    Predicate* ParseQuery();
    Predicate* ParseHeadPredicate();
    Predicate* ParsePredicate();
    void ParsePredicateList(Rule*& rule);
    void ParseParameterList(Predicate*& predicate);
    void ParseStringList(Predicate*& predicate);
    void ParseIdList(Predicate*& predicate);
    Parameter* ParseParameter();
    void MatchTerminal(TokenType typeToMatch);

    DatalogProgram* datalogProgram;
    std::vector<Token*> tokens;
    unsigned int index;

public:
    Parser() {}
    ~Parser() {} // TODO: Define the destructor for Parser
    DatalogProgram* Parse(std::vector<Token*> tokens);
    void PrintStructs();

};


#endif //INTERPRETER_PARSER_H
