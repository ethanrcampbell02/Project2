#ifndef INTERPRETER_PREDICATE_H
#define INTERPRETER_PREDICATE_H

#include <string>
#include <vector>
#include "Parameter.h"

class Predicate {
private:
    std::string id;
    std::vector<Parameter*> parameters;
public:
    Predicate() {}
    ~Predicate() {} // TODO: Define the destructor for Predicate
    void SetId(std::string id);
    void AddParameter(Parameter* parameter);
    Parameter* GetParameter(unsigned int i);
    unsigned int NumParameters();
    std::string ToString();
};


#endif //INTERPRETER_PREDICATE_H
