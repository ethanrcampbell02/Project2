#include "Parser.h"
#include <iostream>

// Checks the syntax of the input program by parsing the vector of tokens generated by the lexer
// While doing so, generates a DatalogProgram object to be handled by the execution engine
DatalogProgram* Parser::Parse(std::vector<Token*> tokens) {
    this->tokens = tokens;
    this->index = 0;

    try {
        ParseDatalogProgram();
        PrintStructs();
    } catch (Token*& badToken) {
        std::cout << badToken->ToString() << std::endl;
    }

    return datalogProgram;
}

// After this function is called, a complete DatalogProgram object will be generated and returned
DatalogProgram* Parser::ParseDatalogProgram() {
    datalogProgram = new DatalogProgram();

    MatchTerminal(TokenType::SCHEMES);
    MatchTerminal(TokenType::COLON);
    datalogProgram->AddScheme(ParseScheme());
    ParseSchemeList();
    MatchTerminal(TokenType::FACTS);
    MatchTerminal(TokenType::COLON);
    ParseFactList();
    MatchTerminal(TokenType::RULES);
    MatchTerminal(TokenType::COLON);
    ParseRuleList();
    MatchTerminal(TokenType::QUERIES);
    MatchTerminal(TokenType::COLON);
    datalogProgram->AddQuery(ParseQuery());
    ParseQueryList();
    MatchTerminal(TokenType::END_OF_FILE);

    return datalogProgram;
}

// Adds each scheme to the DatalogProgram object (except the first)
void Parser::ParseSchemeList() {
    if (tokens.at(index)->GetType() != TokenType::FACTS) {
        datalogProgram->AddScheme(ParseScheme());
        ParseSchemeList();
    }
}

// Adds each fact to the DatalogProgram object
void Parser::ParseFactList() {
    if (tokens.at(index)->GetType() != TokenType::RULES) {
        datalogProgram->AddFact(ParseFact());
        ParseFactList();
    }
}

// Adds each rule to the DatalogProgram object
void Parser::ParseRuleList() {
    if (tokens.at(index)->GetType() != TokenType::QUERIES) {
        datalogProgram->AddRule(ParseRule());
        ParseRuleList();
    }
}

// Adds each query to the DatalogProgram object (except the first)
void Parser::ParseQueryList() {
    if (tokens.at(index)->GetType() != TokenType::END_OF_FILE) {
        datalogProgram->AddQuery(ParseQuery());
        ParseQueryList();
    }
}

// Generates a scheme with an ID and populates it with parameters
Predicate* Parser::ParseScheme() {
    Predicate* scheme = new Predicate();

    scheme->SetId(tokens.at(index)->GetDesc());
    MatchTerminal(TokenType::ID);
    MatchTerminal(TokenType::LEFT_PAREN);

    Parameter* parameter = new Parameter(tokens.at(index)->GetDesc());
    scheme->AddParameter(parameter);
    MatchTerminal(TokenType::ID);

    ParseIdList(scheme);
    MatchTerminal(TokenType::RIGHT_PAREN);

    return scheme;
}

// Generates a fact with an ID and populates it with parameters
Predicate* Parser::ParseFact() {
    Predicate* fact = new Predicate();

    fact->SetId(tokens.at(index)->GetDesc());
    MatchTerminal(TokenType::ID);
    MatchTerminal(TokenType::LEFT_PAREN);

    Parameter* parameter = new Parameter(tokens.at(index)->GetDesc());
    fact->AddParameter(parameter);
    MatchTerminal(TokenType::STRING);

    ParseStringList(fact);
    MatchTerminal(TokenType::RIGHT_PAREN);
    MatchTerminal(TokenType::PERIOD);

    return fact;
}

// Generates a rule with a head predicate and body predicates
Rule* Parser::ParseRule() {
    Rule* rule = new Rule();

    rule->AddHeadPredicate(ParseHeadPredicate());
    MatchTerminal(TokenType::COLON_DASH);
    rule->AddBodyPredicate(ParsePredicate());
    ParsePredicateList(rule);
    MatchTerminal(TokenType::PERIOD);

    return rule;
}

// Generates a query
Predicate* Parser::ParseQuery() {
    Predicate* query;

    query = ParsePredicate();
    MatchTerminal(TokenType::Q_MARK);

    return query;
}

// Generates a head predicate with an ID and parameters
Predicate* Parser::ParseHeadPredicate() {
    Predicate* headPredicate = new Predicate();

    headPredicate->SetId(tokens.at(index)->GetDesc());
    MatchTerminal(TokenType::ID);
    MatchTerminal(TokenType::LEFT_PAREN);

    Parameter* parameter = new Parameter(tokens.at(index)->GetDesc());
    headPredicate->AddParameter(parameter);
    MatchTerminal(TokenType::ID);

    ParseIdList(headPredicate);
    MatchTerminal(TokenType::RIGHT_PAREN);

    return headPredicate;
}

// Generates a predicate (used by ParseQuery)
Predicate* Parser::ParsePredicate() {
    Predicate* predicate = new Predicate();

    predicate->SetId(tokens.at(index)->GetDesc());
    MatchTerminal(TokenType::ID);
    MatchTerminal(TokenType::LEFT_PAREN);

    predicate->AddParameter(ParseParameter());
    ParseParameterList(predicate);
    MatchTerminal(TokenType::RIGHT_PAREN);

    return predicate;
}

// Populates a rule with one predicate then calls itself recursively
void Parser::ParsePredicateList(Rule*& rule) {
    if (tokens.at(index)->GetType() != TokenType::PERIOD) {
        MatchTerminal(TokenType::COMMA);
        rule->AddBodyPredicate(ParsePredicate());
        ParsePredicateList(rule);
    }
}

// Populates a predicate with one parameter then calls itself recursively
void Parser::ParseParameterList(Predicate*& predicate) {
    if (tokens.at(index)->GetType() != TokenType::RIGHT_PAREN) {
        MatchTerminal(TokenType::COMMA);
        predicate->AddParameter(ParseParameter());
        ParseParameterList(predicate);
    }
}

// Populates a predicate with one parameter then calls itself recursively
void Parser::ParseStringList(Predicate*& predicate) {
    if (tokens.at(index)->GetType() != TokenType::RIGHT_PAREN) {
        MatchTerminal(TokenType::COMMA);

        Parameter* parameter = new Parameter(tokens.at(index)->GetDesc());
        predicate->AddParameter(parameter);
        MatchTerminal(TokenType::STRING);

        ParseStringList(predicate);
    }
}

// Populates a predicate with one parameter then calls itself recursively
void Parser::ParseIdList(Predicate*& predicate) {
    if (tokens.at(index)->GetType() != TokenType::RIGHT_PAREN) {
        MatchTerminal(TokenType::COMMA);

        Parameter* parameter = new Parameter(tokens.at(index)->GetDesc());
        predicate->AddParameter(parameter);
        MatchTerminal(TokenType::ID);

        ParseIdList(predicate);
    }
}

// Generates a parameter
Parameter* Parser::ParseParameter() {
    Parameter* parameter = new Parameter(tokens.at(index)->GetDesc());
    if (tokens.at(index)->GetType() == TokenType::STRING) {
        MatchTerminal(TokenType::STRING);
    }
    else {
        MatchTerminal(TokenType::ID);
    }
    return parameter;
}

// Checks if the current input token's type matches the terminal in the production.
// If it does, advance to the next token. If not, throw an exception.
void Parser::MatchTerminal(TokenType typeToMatch) {

    if (tokens.at(index)->GetType() == typeToMatch) {

        // If we are at the END_OF_FILE token, stop here.
        if (tokens.at(index)->GetType() == TokenType::END_OF_FILE) {
            return;
        }
        index++;

        // Skips the token if it is a comment
        if (tokens.at(index)->GetType() == TokenType::COMMENT) {
            index++;
        }

    }
    else {
        throw tokens.at(index);
    }
}

// Prints a string representation of the DatalogProgram object
void Parser::PrintStructs() {
    std::cout << "Success!" << std::endl;
    std::cout << datalogProgram->ToString() << std::endl;
}