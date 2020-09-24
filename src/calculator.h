//
// Created by Korel Kashri
//

#ifndef CALCULATOR_CALCULATOR_H
#define CALCULATOR_CALCULATOR_H

#include <iostream>
#include <vector>
#include <complex>
#include <string>
#include <map>
#include <boost/algorithm/string.hpp>

#include "utilities/translator.h"

using namespace std;

class calculator {
private:
    int calculate_pow(std::vector<double> &numbers, std::vector<char> &methods);
    int calculate_plus_minus(std::vector<double> &numbers, std::vector<char> &methods);
    int calculate_mul_div(std::vector<double> &numbers, std::vector<char> &methods);
    int calculate_parenthesis(std::vector<double> &numbers, std::vector<char> &methods);
    int calculate_parenthesis1(std::vector<double> &numbers, std::vector<char> &methods);

    map<string, double> variables;
    vector<char> available_methods = {'+', '-', '/', '*', '^', '%', '(', ')', '!'};

public:
    calculator();
    double calculate_expression(const string &expression);
    void add_variable(string data);
};


#endif //CALCULATOR_CALCULATOR_H
