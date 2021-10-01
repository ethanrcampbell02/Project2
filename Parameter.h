#ifndef INTERPRETER_PARAMETER_H
#define INTERPRETER_PARAMETER_H

#include <string>

class Parameter {
private:
    std::string p;
public:
    Parameter() {}
    Parameter(std::string p) {
        this->p = p;
    }
    ~Parameter() {} // TODO: Define destructor for Parameter

    std::string ToString();
};


#endif //INTERPRETER_PARAMETER_H
