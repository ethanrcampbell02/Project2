#ifndef INTERPRETER_DATALOGPROGRAM_H
#define INTERPRETER_DATALOGPROGRAM_H

#include "Predicate.h"
#include "Rule.h"
#include <vector>
#include <string>
#include <set>

class DatalogProgram {
private:
    std::vector<Predicate*> schemes;
    std::vector<Predicate*> facts;
    std::vector<Rule*> rules;
    std::vector<Predicate*> queries;
    std::set<std::string> domain;
public:
    DatalogProgram() {}
    ~DatalogProgram() {} // TODO: Define the destructor for DatalogProgram
    void AddScheme(Predicate* scheme);
    void AddFact(Predicate* fact);
    void AddRule(Rule* rule);
    void AddQuery(Predicate*);
    std::string ToString();
};


#endif //INTERPRETER_DATALOGPROGRAM_H
