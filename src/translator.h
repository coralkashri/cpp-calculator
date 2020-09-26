//
// Created by Korel Kashri
//

#ifndef CALCULATOR_TRANSLATOR_H
#define CALCULATOR_TRANSLATOR_H

#include <iostream>
#include <vector>
#include <complex>
#include <string>
#include <bits/stdc++.h>

class translator {
public:
    std::string fix_expression(const std::string &expression);
    std::vector<std::string> process_expression(std::string &expression_str, std::vector<char> &available_methods, std::map<std::string, double> &variables);
    bool validate_parentheses(const std::string &expression_str);

private:
    bool new_number_suspect(std::string &number_str, bool is_positive_number, std::vector<std::string> &exp, std::map<std::string, double> &vars);
};

#endif //CALCULATOR_TRANSLATOR_H