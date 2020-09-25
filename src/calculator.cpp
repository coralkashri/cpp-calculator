//
// Created by Korel Kashri
//

#include "calculator.h"
#include "utilities/exceptions.h"
#include "utilities/designer.h"

calculator::calculator() {
    variables["ans"] = 0;
}

double calculator::calculate_expression(const std::string &expression) {
    std::vector<std::string> expr_data, postfix_expr_data;
    double res;
    translator t;
    if (!t.validate_parentheses(expression)) throw wrong_parentheses_exception();
    std::string fixed_expression = t.fix_expression(expression);
    expr_data = t.process_expression(fixed_expression, available_methods, variables);
    postfix_expr_data = convert_infix_to_postfix(expr_data);
    res = resolve_postfix(postfix_expr_data);
    variables["ans"] = res;
    return res;
}

void calculator::set_variable(const std::string &expression) {
    std::vector<std::string> info;
    translator t;
    std::string fixed_expression = t.fix_expression(expression);
    boost::split(info, fixed_expression, [](char c) { return c == '='; });
    if (info.size() == 1) throw illegal_expression_exception();
    variables[info[0]] = this->calculate_expression(info[1]);
}

std::vector<std::string> calculator::convert_infix_to_postfix(const std::vector<std::string> &infix_expression) {
    std::vector<std::string> postfix_expression;
    std::vector<char> operators_stack;
    for (auto &curr_elem : infix_expression) {
        try { // Operand
            postfix_expression.push_back(std::to_string(std::stod(curr_elem)));
        } catch (std::invalid_argument &e) { // Not operand
            if (curr_elem != ")") {
                if (curr_elem != "(") { // Operator
                    if (!operators_stack.empty()) {
                        for (auto top = operators_stack.back(); !operators_stack.empty() && is_equal_or_higher_operator(top, curr_elem[0]); top = operators_stack.back()) {
                            operators_stack.pop_back();
                            postfix_expression.emplace_back(std::string(1, top));
                        }
                    }
                    operators_stack.push_back(curr_elem[0]);
                } else { // Open parenthesis
                    operators_stack.emplace_back('(');
                }
            } else { // Close parenthesis
                for (auto top = operators_stack.back(); top != '('; top = operators_stack.back()) {
                    operators_stack.pop_back();
                    postfix_expression.emplace_back(std::string(1, top));
                }
                operators_stack.pop_back(); // Remove '('
            }
        }
    }
    if (!operators_stack.empty()) {
        for (auto top = operators_stack.back(); !operators_stack.empty(); top = operators_stack.back()) {
            operators_stack.pop_back();
            postfix_expression.emplace_back(std::string(1, top));
        }
    }

    return postfix_expression;
}

double calculator::resolve_postfix(const std::vector<std::string> &postfix_expression) {
    std::vector<double> numbers_stack;
    for (auto &curr : postfix_expression) {
        try {
            numbers_stack.push_back(std::stod(curr));
        } catch (std::invalid_argument &e) {
            auto n1 = numbers_stack.back();
            numbers_stack.pop_back();
            auto n2 = numbers_stack.back();
            numbers_stack.pop_back();
            numbers_stack.push_back(perform_operator_action(curr[0], n2, n1));
        }
    }
    return numbers_stack.empty() ? 0 : numbers_stack.back();
}

bool calculator::is_equal_or_higher_operator(char op1, char op2) {
    return std::find(available_methods.begin(), available_methods.end(), op1) >= std::find(available_methods.begin(), available_methods.end(), op2);
}

double calculator::perform_operator_action(char op, double n1, double n2) {
    double res = 0;
    if (op == '+') {
        res = n1 + n2;
    } else if (op == '-') {
        res = n1 - n2;
    } else if (op == '*') {
        res = n1 * n2;
    } else if (op == '/') {
        res = n1 / n2;
    } else if (op == '^') {
        res = std::pow(n1, n2);
    } else if (op == '%') {
        res = (size_t)n1 % (size_t)n2;
    }
    return res;
}

void calculator::start() {
    std::string expression;
    bool running = true;
    std::cout << "******************\n" <<
              "**\n" <<
              "** Calculator\n" <<
              "**\n" <<
              "******************\n";
    std::cout << "To add new variable, use the syntax: ~varname=value\n";
    std::cout << "<ans> variable will always hold the last calculated result.\n";
    std::cout << "Press enter to calculate (you can use spaces between chars)." << std::endl;
    while (running) {
        std::cout << "Enter expression: ";
        getline(std::cin, expression);
        try {
            if (expression[0] == '~') {
                if (expression.size() == 1) throw std::runtime_error("Variable assignment missing.");
                std::string temp = expression.data() + 1;
                this->set_variable(temp);
            } else {
                std::cout << expression << " = " << this->calculate_expression(expression) << std::endl;
            }
        } catch (std::exception &e) {
            std::cout << designer::make_colored(std::stringstream() << "Error occurred: " << e.what(), designer::color::RED, true) << std::endl;
        } catch (...) {
            std::cout << designer::make_colored("Error occurred.", designer::color::RED, true) << std::endl;
        }
    }
}