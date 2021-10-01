#include "Lexer.h"
#include "ColonAutomaton.h"
#include "ColonDashAutomaton.h"
#include "TemplateAutomaton.h"
#include "StringAutomaton.h"
#include "SLCommentAutomaton.h"
#include "MLCommentAutomaton.h"
#include "IdentifierAutomaton.h"
#include <iostream>

Lexer::Lexer() {
    CreateAutomata();
}

Lexer::~Lexer() {
    //PrintTokens();
    for (Token* token : tokens) {
        delete token;
    }
    for (Automaton* automaton : automata) {
        delete automaton;
    }
}

void Lexer::CreateAutomata() {
    automata.push_back(new ColonAutomaton());
    automata.push_back(new ColonDashAutomaton());
    automata.push_back(new TemplateAutomaton(TokenType::COMMA));
    automata.push_back(new TemplateAutomaton(TokenType::PERIOD));
    automata.push_back(new TemplateAutomaton(TokenType::Q_MARK));
    automata.push_back(new TemplateAutomaton(TokenType::LEFT_PAREN));
    automata.push_back(new TemplateAutomaton(TokenType::RIGHT_PAREN));
    automata.push_back(new TemplateAutomaton(TokenType::MULTIPLY));
    automata.push_back(new TemplateAutomaton(TokenType::ADD));
    automata.push_back(new TemplateAutomaton(TokenType::SCHEMES));
    automata.push_back(new TemplateAutomaton(TokenType::FACTS));
    automata.push_back(new TemplateAutomaton(TokenType::RULES));
    automata.push_back(new TemplateAutomaton(TokenType::QUERIES));
    automata.push_back(new StringAutomaton());
    automata.push_back(new MLCommentAutomaton());
    automata.push_back(new SLCommentAutomaton());
    automata.push_back(new IdentifierAutomaton());
}

void Lexer::Run(std::string& input) {
    int lineNumber = 1;

    // While there are more characters to tokenize:
    while (input.size() > 0) {
        int maxRead = 0;
        Automaton* maxAutomaton = automata.at(0);

        // Skips this iteration if current character is whitespace
        if ( isspace( input.at(0) ) ) {
            if (input.at(0) == '\n') {
                lineNumber++;
            }
            input.erase(0, 1);
            continue;
        }

        // Input the first character into each automaton and keep track of the one that recognizes the longest string
        for (Automaton* automaton : automata) {
            int inputRead = automaton->Start(input);
            if (inputRead > maxRead) {
                maxRead = inputRead;
                maxAutomaton = automaton;
            }
        }

        // Create a token corresponding to the automaton that recognized the longest string of characters
        if (maxRead > 0) {
            Token* newToken = maxAutomaton->CreateToken(input.substr(0, maxRead), lineNumber);
            lineNumber += maxAutomaton->NewLinesRead();
            tokens.push_back(newToken);
        }
        // If no automata recognized the char, create a single-character UNDEFINED token
        else {
            maxRead = 1;
            Token* newToken = new Token(TokenType::UNDEFINED, input.substr(0, 1), lineNumber);
            tokens.push_back(newToken);
        }

        input.erase(0, maxRead);
    }

    // The input file has been read, add END_OF_FILE token
    Token* newToken = new Token(TokenType::END_OF_FILE, "", lineNumber);
    tokens.push_back(newToken);
}

// Prints the data in every token
void Lexer::PrintTokens() {
    for (Token* token : tokens) {
        std::cout << token->ToString() << std::endl;
    }
    std::cout << "Total Tokens = " << tokens.size();
}

std::vector<Token*> Lexer::GetTokens() {
    return tokens;
}
