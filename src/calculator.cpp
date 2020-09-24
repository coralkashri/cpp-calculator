//
// Created by Korel Kashri
//

#include "calculator.h"

int calculator::calculate_pow(std::vector<double> &numbers, std::vector<char> &methods) {
    int i;
    double ans;
    for (i = 0; i < methods.size(); i++) {
        if (methods[i] == '^') {
            if (numbers.size() < i + 2) {
                throw runtime_error("Error..");
            }
            ans = pow(numbers[i], numbers[i + 1]);
            numbers[i] = ans;
            numbers.erase(numbers.begin() + i + 1);
            methods.erase(methods.begin() + i);
        }
    }
}

int calculator::calculate_plus_minus(std::vector<double> &numbers, std::vector<char> &methods) {
    int i;
    double ans;
    for (i = 0; i < methods.size(); i++) {
        if (methods[i] == '+' || methods[i] == '-') {
            if (numbers.size() < i + 2) {
                throw runtime_error("Error..");
            }
            switch (methods[i]) {
                case '+':
                    ans = numbers[i] + numbers[i + 1];
                    numbers.erase(numbers.begin() + i + 1);
                    break;
                case '-':
                    if (numbers[i + 1] == 0) return false;
                    ans = numbers[i] - numbers[i + 1];
                    numbers.erase(numbers.begin() + i + 1);
                    break;
                default:
                    ans = 0;
                    break;
            }
            numbers[i] = ans;
            methods.erase(methods.begin() + i);
            i--;
        }
    }
    return true;
}

int calculator::calculate_mul_div(std::vector<double> &numbers, std::vector<char> &methods) {
    int i;
    double ans;
    for (i = 0; i < methods.size(); i++) {
        if (methods[i] == '*' || methods[i] == '/' || methods[i] == '!' || methods[i] == '%') {
            if (numbers.size() < i + 2) {
                throw runtime_error("Error..");
            }
            switch (methods[i]) {
                case '*':
                    ans = numbers[i] * numbers[i + 1];
                    numbers.erase(numbers.begin() + i + 1);
                    break;
                case '/':
                    if (numbers[i + 1] == 0) return false;
                    ans = numbers[i] / numbers[i + 1];
                    numbers.erase(numbers.begin() + i + 1);
                    break;
                case '!':
                    //ans = Atseret((int)E[i]);
                    ans = 0;
                    break;
                case '%':
                    ans = (int) numbers[i] % (int) numbers[i + 1];
                    numbers.erase(numbers.begin() + i + 1);
                    break;
                default:
                    ans = 0;
                    break;
            }
            numbers[i] = ans;
            methods.erase(methods.begin() + i);
            i--;
        }
    }
    return true;
}

int calculator::calculate_parenthesis(std::vector<double> &numbers, std::vector<char> &methods) {
    int i, j;
    double ans;
    int IsFoundStart = 0;
    vector<double> inner_level_nums;
    vector<char> inner_level_methods;
    for (i = 0; i < numbers.size() - 1; i++) {
        if (IsFoundStart == 2 && methods[i] == ')') break;
        if (methods[i] == '(') {
            IsFoundStart = 1;
            if (methods[i + 1] == ')') {
                methods.erase(methods.begin() + i);
                methods.erase(methods.begin() + i);
                return 1;
            }
            methods.erase(methods.begin() + i);
            for (j = i; j < methods.size(); j++) {
                if (methods[j] == ')') {
                    IsFoundStart = 2;
                    methods.erase(methods.begin() + j);
                    break;
                }
                if (inner_level_nums.empty()) {
                    if (methods[j] == '(')
                        calculate_parenthesis(numbers, methods);
                    {
                        inner_level_nums.push_back(numbers[j]);
                        numbers.erase(numbers.begin() + j);
                        inner_level_methods.push_back(methods[j]);
                        methods.erase(methods.begin() + j);
                    }
                } else {
                    if (methods[j] == '(')
                        calculate_parenthesis(numbers, methods);
                    {
                        inner_level_methods.push_back(methods[j]);
                        methods.erase(methods.begin() + j);
                    }
                }
                if (methods[methods.size() - 1] != '(') {
                    if (methods[j] == '(')
                        calculate_parenthesis(numbers, methods);
                    {
                        inner_level_nums.push_back(numbers[j]);
                        numbers.erase(numbers.begin() + j);
                        j--;
                    }
                }
            }
            //if (nums.Count == methods.Count)
            //    nums.Insert(0, 0.0);
            try {
                if (calculate_parenthesis(inner_level_nums, inner_level_methods) == 0) return 0;
                calculate_pow(inner_level_nums, inner_level_methods);
                if (!calculate_mul_div(inner_level_nums, inner_level_methods)) return 0;
                calculate_plus_minus(inner_level_nums, inner_level_methods);
                ans = inner_level_nums[0];
                numbers.insert(numbers.begin() + i, ans);
                inner_level_nums.clear();
                inner_level_methods.clear();
            } catch (...) {
                throw runtime_error("Error..");
            }
        }
    }
    return 2;
}

calculator::calculator() {
}

double calculator::calculate_expression(const string &expression) {
    Translator::Expression exp;
    try {
        string fixed_expression = Translator::fix_expression(expression);
        exp = Translator::convert_expression(fixed_expression, available_methods, variables);
        calculate_parenthesis(exp.numbers, exp.methods);
        calculate_pow(exp.numbers, exp.methods);
        calculate_mul_div(exp.numbers, exp.methods);
        calculate_plus_minus(exp.numbers, exp.methods);
    } catch (std::runtime_error &e) {
        throw runtime_error("Error occurred: Invalid expression.");
    } catch (...) {
        throw runtime_error("Error occurred: Invalid expression.");
    }
    return exp.numbers[0];
}

void calculator::add_variable(string expression) {
    std::vector<std::string> info;
    boost::split(info, expression, [](char c) { return c == '='; });
    variables[info[0]] = this->calculate_expression(info[1]);
}
