#include "DatalogProgram.h"
#include <sstream>

void DatalogProgram::AddScheme(Predicate* scheme) {
    schemes.push_back(scheme);
}

void DatalogProgram::AddFact(Predicate* fact) {
    facts.push_back(fact);

    for (unsigned int i = 0; i < fact->NumParameters(); i++) {
        Parameter* parameter = fact->GetParameter(i);
        domain.insert(parameter->ToString());
    }

}

void DatalogProgram::AddRule(Rule* rule) {
    rules.push_back(rule);
}

void DatalogProgram::AddQuery(Predicate* query) {
    queries.push_back(query);
}

// Generates a string representation of the DatalogProgram
std::string DatalogProgram::ToString() {
    std::stringstream ss;

    ss << "Schemes(" << schemes.size() << "):" << std::endl;

    for(Predicate* scheme : schemes) {
        ss << "  " << scheme->ToString() << std::endl;
    }

    ss << "Facts(" << facts.size() << "):" << std::endl;

    for(Predicate* fact : facts) {
        ss << "  " << fact->ToString() << "." << std::endl;
    }

    ss << "Rules(" << rules.size() << "):" << std::endl;

    for(Rule* rule : rules) {
        ss << "  " << rule->ToString() << std::endl;
    }

    ss << "Queries(" << queries.size() << "):" << std::endl;

    for(Predicate* query : queries) {
        ss << "  " << query->ToString() << "?" << std::endl;
    }

    ss << "Domain(" << domain.size() << "):" << std::endl;

    for(auto elem : domain) {
        ss << "  " << elem << std::endl;
    }

    return ss.str();
}