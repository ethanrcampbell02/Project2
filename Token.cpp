#include "Token.h"
#include <map>

Token::Token(TokenType type, std::string description, int line) {
    this->type = type;
    this->description = description;
    this->line = line;
}

// Returns a string representation of the token's data
std::string Token::ToString() {
    std::map<TokenType, std::string> typeToString;

    typeToString.insert({TokenType::COMMA,       "COMMA"});
    typeToString.insert({TokenType::PERIOD,      "PERIOD"});
    typeToString.insert({TokenType::Q_MARK,      "Q_MARK"});
    typeToString.insert({TokenType::LEFT_PAREN,  "LEFT_PAREN"});
    typeToString.insert({TokenType::RIGHT_PAREN, "RIGHT_PAREN"});
    typeToString.insert({TokenType::COLON,       "COLON"});
    typeToString.insert({TokenType::COLON_DASH,  "COLON_DASH"});
    typeToString.insert({TokenType::MULTIPLY,    "MULTIPLY"});
    typeToString.insert({TokenType::ADD,         "ADD"});
    typeToString.insert({TokenType::SCHEMES,     "SCHEMES"});
    typeToString.insert({TokenType::FACTS,       "FACTS"});
    typeToString.insert({TokenType::RULES,       "RULES"});
    typeToString.insert({TokenType::QUERIES,     "QUERIES"});
    typeToString.insert({TokenType::ID,          "ID"});
    typeToString.insert({TokenType::STRING,      "STRING"});
    typeToString.insert({TokenType::COMMENT,     "COMMENT"});
    typeToString.insert({TokenType::UNDEFINED,   "UNDEFINED"});
    typeToString.insert({TokenType::END_OF_FILE, "EOF"});

    std::string tokenStr = "(" + typeToString.at(type) + ",\"" + description + "\"," + std::to_string(line) + ")";

    return tokenStr;
}

TokenType Token::GetType() {
    return this->type;
}

std::string Token::GetDesc() {
    return this->description;
}
