//
// Created by Korel Kashri
//

#include "calculator.h"

using namespace std;

int main() {
    string expression;
    std::cout.unsetf(std::ios::floatfield);                // floatfield not set
    std::cout.precision(1000);
    calculator c;
    bool running = true;
    cout << "******************" << endl <<
            "**" << endl <<
            "** calculator" << endl <<
            "**" << endl <<
            "******************" << endl;
    cout << "To add new variable, use the syntax: ~varname=value" << endl;
    cout << "Press enter to calculate (you can use spaces between chars)." << endl;
    while (running) {
        cout << "Enter expression: ";
        getline(cin, expression);
        if (expression[0] == '~') {
            string temp = expression.data() + 1;
            try {
                c.add_variable(temp);
            } catch (std::invalid_argument &e) {
                cerr << "Invalid syntax." << endl;
                sleep(1);
            }
        } else {
            try {
                cout << expression << " = " << c.calculate_expression(expression) << endl;
            } catch (std::exception &e) {
                cerr << "Invalid syntax." << endl;
            } catch (...) {
                cerr << "Invalid syntax." << endl;
            }
        }
    }
    return 0;
}