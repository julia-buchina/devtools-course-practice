// Copyright 2014 Julia Buchina

#include "include/fraction.h"
#include "include/fraction_calculator_application.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <string>
#include <sstream>

Expression::Expression() : arg1(Fraction()), arg2(Fraction()), operation("") {}
CalculatorApplication::CalculatorApplication() : message_("") {}

void CalculatorApplication::help(const char* appname, const char* message) {
    message_ = std::string(message)
             + std::string("This is a fraction calculator application.\n\n")
             + "Please provide arguments in the following format:\n\n"
             + "  $ " + appname + " <argument1> <argument2>"
             + " <argument3> <argument4> <operation>\n\n"
             + "Where all arguments are integer numbers, "
             + "and <operation> is one of '+', '-', '*' or '/'.\n";
}

int64_t parseInteger(const char* arg);
int64_t parseInteger(const char* arg) {
    char* end;
    int64_t value = strtol(arg, &end, 10);

    if (end[0]) {
        throw "Wrong number format\n";
    }

    return value;
}

bool CalculatorApplication::parseArguments(int argc, const char** argv,
                                           Expression* expresson) {
    if (argc == 1) {
        help(argv[0]);
        return false;
    } else if (argc != 6) {
        message_ = "ERROR: Should be 5 arguments.\n\n";
        help(argv[0]);
        return false;
    }

    try {
        int a = static_cast<int>(parseInteger(argv[1]));
        int b = static_cast<int>(parseInteger(argv[2]));
        int c = static_cast<int>(parseInteger(argv[3]));
        int d = static_cast<int>(parseInteger(argv[4]));
        expresson->arg1 = Fraction(a, b);
        expresson->arg2 = Fraction(c, d);
    }
    catch(...) {
        message_ = "Wrong number format!\n";
        return false;
    }

    const char* op = argv[5];
    if ((strlen(op) != 1) ||
        (*op != '+' && *op != '-' && *op != '*' && *op != '/')) {
        message_ = std::string(op) + " - Wrong operation!\n";
        return false;
    } else {
        expression->operation = *op;
    }

    return true;
}

std::string CalculatorApplication::operator()(int argc, const char** argv) {
    Expression expr;

    bool returnCode = parseArguments(argc, argv, &expr);
    if (returnCode != true)
        return message_;

    Fraction result;
    std::ostringstream stream;
    stream << "Result = ";

    switch (expr.operation) {
     case '+':
        result = expr.arg1 + expr.arg2;
        stream << result.getNumerator() << " ";
        stream << result.getDenominator();
        break;
     case '-':
        result = expr.arg1 - expr.arg2;
        stream << result.getNumerator() << " ";
        stream << result.getDenominator();
        break;
     case '*':
        result = expr.arg1 * expr.arg2;
        stream << result.getNumerator() << " ";
        stream << result.getDenominator();
        break;
     case '/':
        result = expr.arg1 / expr.arg2;
        stream << result.getNumerator() << " ";
        stream << result.getDenominator();
        break;
    }

    message_ = stream.str();

    return message_;
}
