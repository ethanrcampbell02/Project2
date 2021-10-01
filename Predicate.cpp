#include "Predicate.h"
#include <sstream>

void Predicate::SetId(std::string id) {
    this->id = id;
}

void Predicate::AddParameter(Parameter* parameter) {
    parameters.push_back(parameter);
}

Parameter* Predicate::GetParameter(unsigned int i) {
    return parameters.at(i);
}

unsigned int Predicate::NumParameters() {
    return parameters.size();
}

std::string Predicate::ToString() {
    std::stringstream ss;
    ss << id << "(";

    for (Parameter* parameter : parameters) {
        ss << parameter->ToString();
        if (parameter != parameters.at(parameters.size() - 1)) {
            ss << ",";
        }
    }

    ss << ")";

    return ss.str();
}