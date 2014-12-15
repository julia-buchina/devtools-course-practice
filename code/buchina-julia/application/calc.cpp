// Copyright 2014 Julia Buchina

#include <stdio.h>
#include <string>

#include "include/fraction_calculator_application.h"

int main(int argc, const char** argv) {
    CalculatorApplication app;
    std::string output = app(argc, argv);
    printf("%s\n", output.c_str());
    return 0;
}
