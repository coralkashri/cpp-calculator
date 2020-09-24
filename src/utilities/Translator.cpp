//
// Created by Korel Kashri
//

#include "Translator.h"

namespace Translator {
    std::string fix_expression(const std::string &expression) {
        std::string fixed_expression;
        for (auto& c : expression) {
            if (c != '=' && c != ' ') {
                fixed_expression += c;
            }
        }
        return fixed_expression;
    }

    void new_number_suspect(std::string &number, size_t &nomwnb, Expression &exp, std::map<std::string, double> &vars) {
        if (!number.empty()) {
            try {
                if (nomwnb == 2) {
                    number = exp.methods[exp.methods.size() - 1] + number;
                    exp.methods.pop_back();
                }
                exp.numbers.push_back(std::stod(number));
            } catch (std::invalid_argument &e) { // The current part
                auto it = vars.find(number);
                if (it != vars.end()) { // If the current part is variable
                    exp.numbers.push_back(it->second);
                } else {
                    if (number[0] == 'e') {
                        try {
                            std::string temp = number.data() + 1;
                            int e_number = std::stoi(temp);
                            exp.numbers.push_back(std::pow(10, e_number));
                        } catch (std::runtime_error &e) {
                            throw std::runtime_error("Can't find variable..");
                        }
                    } else {
                        throw std::runtime_error("Can't find variable..");
                    }
                }
            }
            number = "";
            nomwnb = 0;
        }
    }

    Expression convert_expression(std::string &expression, std::vector<char> &available_methods, std::map<std::string, double> &variables) {
        Expression exp;
        std::string current_part;
        size_t number_of_methods_without_number_between = 0;
        size_t i = 0;
        for (auto& c : expression) {
            if (std::find(available_methods.begin(), available_methods.end(), c) == available_methods.end()) {
                current_part += c;
            } else { // c is method and current_part is the part before this method

                new_number_suspect(current_part, number_of_methods_without_number_between, exp, variables);

                exp.methods.push_back(c);
                if (c != '(' && c != ')')
                    number_of_methods_without_number_between++;
                if (number_of_methods_without_number_between == 2)
                {
                    //if (c != '-' && c != '+') {
                        if (i != 0)
                            number_of_methods_without_number_between = 0;
                        exp.numbers.push_back(0.0);
                    //}
                }
            }
            i++;
        }

        // Add 0 in the beginning to solve the problem: (-1) + 2
        i = 0;
        if (expression[i] == '(') while (expression[i] == '(' || expression[i] == ')') i++;
        std::string temp;
        temp += expression[i];
        if (std::find(available_methods.begin(), available_methods.end(), expression[i]) != available_methods.end()) {
            exp.numbers.insert(exp.numbers.begin(), 0.0); // Probably Minus Or Plus sent this to here
        }

        new_number_suspect(current_part, number_of_methods_without_number_between, exp, variables);
        return exp;
    }
}