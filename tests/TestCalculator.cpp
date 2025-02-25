#include <gtest/gtest.h>
#include <memory>
#include <string>
#include <map>
#include <stdexcept>

// Include the definitions from your main source code.
// For demonstration, we assume the classes are available here.
// In a real project, you would separate the classes into header files.

class Inode {
public:
    virtual ~Inode() {}
    virtual double calc() = 0;
    virtual std::string print() = 0;
};

class Value : public Inode {
    double value;
public:
    Value(double v) : value(v) {}
    double calc() override { return value; }
    std::string print() override { return std::to_string(value); }
};

class Sum : public Inode {
    std::shared_ptr<Inode> left;
    std::shared_ptr<Inode> right;
public:
    Sum(std::shared_ptr<Inode> l, std::shared_ptr<Inode> r)
        : left(l), right(r) {}
    double calc() override { return left->calc() + right->calc(); }
    std::string print() override {
        return "(" + left->print() + " + " + right->print() + ")";
    }
};

class Subtract : public Inode {
    std::shared_ptr<Inode> left;
    std::shared_ptr<Inode> right;
public:
    Subtract(std::shared_ptr<Inode> l, std::shared_ptr<Inode> r)
        : left(l), right(r) {}
    double calc() override { return left->calc() - right->calc(); }
    std::string print() override {
        return "(" + left->print() + " - " + right->print() + ")";
    }
};

class Multiply : public Inode {
    std::shared_ptr<Inode> left;
    std::shared_ptr<Inode> right;
public:
    Multiply(std::shared_ptr<Inode> l, std::shared_ptr<Inode> r)
        : left(l), right(r) {}
    double calc() override { return left->calc() * right->calc(); }
    std::string print() override {
        return "(" + left->print() + " * " + right->print() + ")";
    }
};

class Divide : public Inode {
    std::shared_ptr<Inode> left;
    std::shared_ptr<Inode> right;
public:
    Divide(std::shared_ptr<Inode> l, std::shared_ptr<Inode> r)
        : left(l), right(r) {}
    double calc() override {
        double divisor = right->calc();
        if (divisor == 0)
            throw std::runtime_error("Division by zero");
        return left->calc() / divisor;
    }
    std::string print() override {
        return "(" + left->print() + " / " + right->print() + ")";
    }
};

// Test for the Sum operation
TEST(CalculatorTests, TestSum) {
    auto left = std::make_shared<Value>(4);
    auto right = std::make_shared<Value>(5);
    Sum sum(left, right);
    EXPECT_DOUBLE_EQ(sum.calc(), 9);
    std::string expected = "(" + left->print() + " + " + right->print() + ")";
    EXPECT_EQ(sum.print(), expected);
}

// Test for the Subtract operation
TEST(CalculatorTests, TestSubtract) {
    auto left = std::make_shared<Value>(10);
    auto right = std::make_shared<Value>(3);
    Subtract subtract(left, right);
    EXPECT_DOUBLE_EQ(subtract.calc(), 7);
    std::string expected = "(" + left->print() + " - " + right->print() + ")";
    EXPECT_EQ(subtract.print(), expected);
}

// Test for the Multiply operation
TEST(CalculatorTests, TestMultiply) {
    auto left = std::make_shared<Value>(6);
    auto right = std::make_shared<Value>(7);
    Multiply multiply(left, right);
    EXPECT_DOUBLE_EQ(multiply.calc(), 42);
    std::string expected = "(" + left->print() + " * " + right->print() + ")";
    EXPECT_EQ(multiply.print(), expected);
}

// Test for the Divide operation
TEST(CalculatorTests, TestDivide) {
    auto left = std::make_shared<Value>(20);
    auto right = std::make_shared<Value>(4);
    Divide divide(left, right);
    EXPECT_DOUBLE_EQ(divide.calc(), 5);
    std::string expected = "(" + left->print() + " / " + right->print() + ")";
    EXPECT_EQ(divide.print(), expected);
}

// Test for division by zero (should throw an exception)
TEST(CalculatorTests, TestDivideByZero) {
    auto left = std::make_shared<Value>(20);
    auto right = std::make_shared<Value>(0);
    Divide divide(left, right);
    EXPECT_THROW(divide.calc(), std::runtime_error);
}

// Test for combined operations
TEST(CalculatorTests, TestCombinedOperations) {
    auto v1 = std::make_shared<Value>(10);
    auto v2 = std::make_shared<Value>(5);
    auto v3 = std::make_shared<Value>(2);
    // (10 + 5) * 2 should equal 30
    auto sum = std::make_shared<Sum>(v1, v2);
    Multiply multiply(sum, v3);
    EXPECT_DOUBLE_EQ(multiply.calc(), 30);
    std::string expected = "(" + sum->print() + " * " + v3->print() + ")";
    EXPECT_EQ(multiply.print(), expected);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
