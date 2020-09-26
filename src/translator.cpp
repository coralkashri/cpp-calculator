//
// Created by Korel Kashri
//

#include "translator.h"
#include "utilities/exceptions.h"

std::string translator::fix_expression(const std::string &expression) {
    std::string fixed_expression;
    for (auto& c : expression) {
        if (c != ' ') {
            fixed_expression += c;
        }
    }
    return fixed_expression;
}

bool translator::new_number_suspect(std::string &number_str, bool is_positive_number, std::vector<std::string> &exp, std::map<std::string, double> &vars) {
    bool is_new_number = false;
    if (!number_str.empty()) {
        try {
            char number_sign = is_positive_number ? '+' : '-';
            exp.emplace_back(std::to_string(std::stod(number_sign + number_str))); // Try to enter a regular number
            is_new_number = true;
        } catch (std::invalid_argument &e) {
            auto it = vars.find(number_str);
            if (it != vars.end()) { // If the current part is variable
                auto number = it->second;
                if (!is_positive_number) number *= -1;
                exp.push_back(std::to_string(number));
                is_new_number = true;
            } else throw variable_not_found_exception();
        }
        number_str = "";
    }
    return is_new_number;
}

std::vector<std::string> translator::process_expression(std::string &expression_str, std::vector<char> &available_methods, std::map<std::string, double> &variables) {
    std::vector<std::string> exp;
    std::string current_part;
    bool is_positive_number = true;
    bool is_magnitude_action = false;
    for (auto &c : expression_str) {
        if (std::find(available_methods.begin(), available_methods.end(), c) == available_methods.end()) {
            current_part += c;
        } else { // c is a method and current_part is the part before this method
            if (current_part.empty()) { // A method without a number before
                if ((c == '-' || c == '+') && (exp.empty() || exp.back() != ")")) { // Change the following number magnitude
                    is_positive_number = (c == '-') ? !is_positive_number : is_positive_number;
                    is_magnitude_action = true; // Which means that there is no new method to record
                } else if (!exp.empty() && exp.back() != ")") {
                    if (c == '+') {
                        is_magnitude_action = true; // Which means that there is no new method to record
                    } else if (c == ')' && is_magnitude_action) throw illegal_expression_exception(); // The parentheses ended with a series of '+' or '-' chars
                    if (!std::set{'-', '+', '(', ')'}.contains(c))
                        throw illegal_expression_exception(); // If the previous char wasn't a parenthesis and the current char is not in {'-', '+', '(', ')'} throw exception
                }
            } else {
                if (new_number_suspect(current_part, is_positive_number, exp, variables)) {
                    is_positive_number = true;
                    is_magnitude_action = false;
                }
            }
            if (!is_magnitude_action) {
                exp.emplace_back(std::string(1, c));
            }
        }
    }
    if (!new_number_suspect(current_part, is_positive_number, exp, variables) && is_magnitude_action)
        throw illegal_expression_exception(); // The expression ended with a series of '+' or '-' chars
    return exp;
}

bool translator::validate_parentheses(const std::string &expression_str) {
    int open_parentheses_count = 0;
    for (auto &c : expression_str) {
        if (c == '(') open_parentheses_count++;
        if (c == ')') open_parentheses_count--;
        if (open_parentheses_count < 0) break;
    }
    return !open_parentheses_count;
}
