//
// Created by Korel Kashri
//

#include "calculator.h"

using namespace std;

int main() {
    string expression;
    std::cout.unsetf(std::ios::floatfield);
    std::cout.precision(1000);
    calculator c;
    c.start();
    return EXIT_SUCCESS;
}