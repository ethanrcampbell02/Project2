#include "Rule.h"
#include <sstream>

void Rule::AddHeadPredicate(Predicate* headPredicate) {
    this->headPredicate = headPredicate;
}

void Rule::AddBodyPredicate(Predicate* bodyPredicate) {
    bodyPredicates.push_back(bodyPredicate);
}

std::string Rule::ToString() {
   std::stringstream ss;

   ss << headPredicate->ToString() << " :- ";

   for (Predicate* predicate : bodyPredicates) {
       ss << predicate->ToString();
       if (predicate != bodyPredicates.at(bodyPredicates.size() - 1)) {
           ss << ",";
       }
   }

   ss << ".";
   return ss.str();
}