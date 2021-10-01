#ifndef INTERPRETER_RULE_H
#define INTERPRETER_RULE_H

#include "Predicate.h"
#include <vector>
#include <string>

class Rule {
private:
    Predicate* headPredicate;
    std::vector<Predicate*> bodyPredicates;
public:
    Rule() {}
    ~Rule() {} // TODO: Define destructor for Rule
    void AddHeadPredicate(Predicate* headPredicate);
    void AddBodyPredicate(Predicate* bodyPredicate);
    std::string ToString();
};


#endif //INTERPRETER_RULE_H
