// Copyright 2014 Julia Buchina

#ifndef CODE_BUCHINA_JULIA_INCLUDE_FRACTION_CALCULATOR_APPLICATION_H_
#define CODE_BUCHINA_JULIA_INCLUDE_FRACTION_CALCULATOR_APPLICATION_H_

#include <string>
#include "include/fraction.h"

#pragma pack(push, 1)
class Expression {
 public:
    Fraction arg1;
    Fraction arg2;
    char operation;
    Expression();
};
#pragma pack(pop)

class CalculatorApplication {
 public:
    CalculatorApplication();

    std::string operator()(int argc, const char** argv);

 private:
    std::string message_;

    void help(const char* appname, const char* message = "");
    bool parseArguments(int argc, const char** argv, Expression* expr);
};

#endif  // CODE_BUCHINA_JULIA_INCLUDE_FRACTION_CALCULATOR_APPLICATION_H_
