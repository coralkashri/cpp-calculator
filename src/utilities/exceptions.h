//
// Created by Korel Kashri
//

#ifndef CALCULATOR_EXCEPTIONS_H
#define CALCULATOR_EXCEPTIONS_H

#include <iostream>

class wrong_parentheses_exception : public std::exception {
public:
    virtual const char* what() const noexcept {
        return "Wrong usage of parentheses.";
    }
};

class variable_not_found_exception : public std::exception {
public:
    virtual const char* what() const noexcept {
        return "Variable not found.";
    }
};

class illegal_expression_exception : public std::exception {
public:
    virtual const char* what() const noexcept {
        return "Expression syntax error detected.";
    }
};

#endif //CALCULATOR_EXCEPTIONS_H