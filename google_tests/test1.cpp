#include "gtest/gtest.h"
#include "../src/calculator.h"

TEST(ParenthesisTest, StartWithParenthesis) {
    calculator calc;
    EXPECT_EQ(calc.calculate_expression("(6*2)+ 3"), (6 * 2) + 3);
}

TEST(ParenthesisTest, EndWithParenthesis) {
    calculator calc;
    EXPECT_EQ(calc.calculate_expression("3 + (6*2)"), 3 + (6 * 2));
}

TEST(ParenthesisTest, MiddleParenthesis) {
    calculator calc;
    EXPECT_EQ(calc.calculate_expression("3 + (6*2) * 2 + 1"), 3 + (6 * 2) * 2 + 1);
}

TEST(ParenthesisTest, NoParenthesis) {
    calculator calc;
    EXPECT_EQ(calc.calculate_expression("3 + 6*2"), 3 + 6 * 2);
}

TEST(ParenthesisTest, ComplplexParenthesis) {
    calculator calc;
    EXPECT_EQ(calc.calculate_expression("(((-3) * 2) * -1 * ( 2 + 3 ))"), (((-3) * 2) * -1 * ( 2 + 3 )));
}

TEST(RegularTest, PositiveNumber) {
    calculator calc;
    EXPECT_EQ(calc.calculate_expression("50"), 50);
}

TEST(RegularTest, NegativeNumber) {
    calculator calc;
    EXPECT_EQ(calc.calculate_expression("-50"), -50);
}

TEST(RegularTest, Test1) {
    calculator calc;
    EXPECT_EQ(calc.calculate_expression("+1-2"), +1-2);
    EXPECT_EQ(calc.calculate_expression("-1-2"), -1-2);
    EXPECT_EQ(calc.calculate_expression("1-2"), 1-2);
    EXPECT_EQ(calc.calculate_expression("1++2"), 1+2);
    EXPECT_EQ(calc.calculate_expression("1+-2"), 1+-2);
    EXPECT_EQ(calc.calculate_expression("-1+-2"), -1+-2);
    EXPECT_EQ(calc.calculate_expression("----1+-+-2"), 1+2);
    EXPECT_EQ(calc.calculate_expression("-----1+--+-2"), -1-2);
}

TEST(VariablesTest, Test1) {
    calculator calc;
    EXPECT_EQ(calc.calculate_expression("-50"), -50);
    EXPECT_EQ(calc.calculate_expression("ans"), -50);
}

TEST(VariablesTest, Test2) {
    calculator calc;
    EXPECT_EQ(calc.calculate_expression("-50"), -50);
    EXPECT_EQ(calc.calculate_expression("ans * -1 + 2"), 52);
}

TEST(VariablesTest, Test3) {
    calculator calc;
    calc.set_variable("my_var =  6 + 9 * 2");
    auto my_var = 6 + 9 * 2;
    EXPECT_EQ(calc.calculate_expression("my_var"), my_var);
    auto ans = my_var * (2 + 6) * std::pow(2, 3);
    EXPECT_EQ(calc.calculate_expression("my_var * (2 + 6) * 2 ^ 3"), ans);
    EXPECT_EQ(calc.calculate_expression("ans * my_var"), ans * my_var);
}

TEST(VariablesTest, Test4) {
    calculator calc;
    calc.set_variable("my_var =  6 + 9 * 2");
    auto my_var = 6 + 9 * 2;
    calc.set_variable("my_var =  my_var + 1");
    my_var++;
    EXPECT_EQ(calc.calculate_expression("my_var"), my_var);
    auto ans = my_var * (2 + 6) * std::pow(2, 3);
    EXPECT_EQ(calc.calculate_expression("my_var * (2 + 6) * 2 ^ 3"), ans);
    EXPECT_EQ(calc.calculate_expression("ans * (my_var + 1)"), ans * (my_var + 1));
}