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

namespace translator {
    struct expression {
        std::vector<double> numbers;
        std::vector<char>   methods;
    };

    std::string     fix_expression(const std::string &expression);
    expression      convert_expression(std::string &expression, std::vector<char> &available_methods, std::map<std::string, double> &variables);
    void            new_number_suspect(std::string &number, size_t &nomwnb, expression &exp, std::map<std::string, double> &vars);
};


#endif //CALCULATOR_TRANSLATOR_H
