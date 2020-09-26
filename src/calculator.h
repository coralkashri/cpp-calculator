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

#include "translator.h"

class calculator {
public:
    calculator();
    void start();
    double calculate_expression(const std::string &expression);
    void set_variable(const std::string &expression);

private:
    std::vector<std::string> convert_infix_to_postfix(const std::vector<std::string> &infix_expression);
    double resolve_postfix(const std::vector<std::string> &postfix_expression);
    bool is_equal_or_higher_operator(char op1, char op2);
    double perform_operator_action(char op, double n1, double n2);

    std::map<std::string, double> variables;
    std::vector<char> available_methods = {'(', ')', '+', '-', '/', '*', '%', '^'/*todo, '!'*/};
};

#endif //CALCULATOR_CALCULATOR_H