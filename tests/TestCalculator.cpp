#include <gtest/gtest.h>
#include <memory>
#include <string>
#include <map>
#include <stdexcept>
#include "Inode.h"
#include "Value.h"
#include "Operators.h"

TEST(CalculatorTests, TestSum) {
    auto left = std::make_shared<Value>(4);
    auto right = std::make_shared<Value>(5);
    Sum sum(left, right);
    EXPECT_DOUBLE_EQ(sum.calc(), 9);
    std::string expected = "(" + left->print() + " + " + right->print() + ")";
    EXPECT_EQ(sum.print(), expected);
}

TEST(CalculatorTests, TestSubtract) {
    auto left = std::make_shared<Value>(10);
    auto right = std::make_shared<Value>(3);
    Subtract subtract(left, right);
    EXPECT_DOUBLE_EQ(subtract.calc(), 7);
    std::string expected = "(" + left->print() + " - " + right->print() + ")";
    EXPECT_EQ(subtract.print(), expected);
}

TEST(CalculatorTests, TestMultiply) {
    auto left = std::make_shared<Value>(6);
    auto right = std::make_shared<Value>(7);
    Multiply multiply(left, right);
    EXPECT_DOUBLE_EQ(multiply.calc(), 42);
    std::string expected = "(" + left->print() + " * " + right->print() + ")";
    EXPECT_EQ(multiply.print(), expected);
}

TEST(CalculatorTests, TestDivide) {
    auto left = std::make_shared<Value>(20);
    auto right = std::make_shared<Value>(4);
    Divide divide(left, right);
    EXPECT_DOUBLE_EQ(divide.calc(), 5);
    std::string expected = "(" + left->print() + " / " + right->print() + ")";
    EXPECT_EQ(divide.print(), expected);
}

TEST(CalculatorTests, TestDivideByZero) {
    auto left = std::make_shared<Value>(20);
    auto right = std::make_shared<Value>(0);
    Divide divide(left, right);
    EXPECT_THROW(divide.calc(), std::runtime_error);
}

TEST(CalculatorTests, TestCombinedOperations) {
    auto v1 = std::make_shared<Value>(10);
    auto v2 = std::make_shared<Value>(5);
    auto v3 = std::make_shared<Value>(2);
    auto sum = std::make_shared<Sum>(v1, v2);
    Multiply multiply(sum, v3);
    EXPECT_DOUBLE_EQ(multiply.calc(), 30);
    std::string expected = "(" + sum->print() + " * " + v3->print() + ")";
    EXPECT_EQ(multiply.print(), expected);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
