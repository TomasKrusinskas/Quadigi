#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <memory>
#include <stdexcept>
#include <cctype>

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

class Variable : public Inode {
    std::string name;
    double value;
    bool isSet;
public:
    Variable(const std::string &n) : name(n), value(0.0), isSet(false) {}
    void setValue(double v) { value = v; isSet = true; }
    double calc() override {
        if (!isSet) {
            std::cout << "Enter value for " << name << ": ";
            std::cin >> value;
            isSet = true;
        }
        return value;
    }
    std::string print() override { return name; }
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

class Parser {
    std::string input;
    size_t pos;
    std::map<std::string, std::shared_ptr<Variable>> &varTable;
    
    void skipWhitespace() {
        while(pos < input.size() && std::isspace(input[pos]))
            pos++;
    }
    
    char peek() {
        skipWhitespace();
        if (pos < input.size())
            return input[pos];
        return '\0';
    }
    
    char get() {
        skipWhitespace();
        if (pos < input.size())
            return input[pos++];
        return '\0';
    }
    
public:
    Parser(const std::string &in, std::map<std::string, std::shared_ptr<Variable>> &table)
        : input(in), pos(0), varTable(table) {}
    
    std::shared_ptr<Inode> parseExpression() {
        auto node = parseTerm();
        while (true) {
            skipWhitespace();
            char op = peek();
            if (op == '+' || op == '-') {
                get();
                auto right = parseTerm();
                if (op == '+')
                    node = std::make_shared<Sum>(node, right);
                else
                    node = std::make_shared<Subtract>(node, right);
            } else {
                break;
            }
        }
        return node;
    }
    
    std::shared_ptr<Inode> parseTerm() {
        auto node = parseFactor();
        while (true) {
            skipWhitespace();
            char op = peek();
            if (op == '*' || op == '/') {
                get();
                auto right = parseFactor();
                if (op == '*')
                    node = std::make_shared<Multiply>(node, right);
                else
                    node = std::make_shared<Divide>(node, right);
            } else {
                break;
            }
        }
        return node;
    }
    
    std::shared_ptr<Inode> parseFactor() {
        skipWhitespace();
        char c = peek();
        if (c == '(') {
            get();
            auto node = parseExpression();
            if (get() != ')') {
                throw std::runtime_error("Expected ')'");
            }
            return node;
        } else if (std::isdigit(c) || c == '.') {
            return parseNumber();
        } else if (std::isalpha(c)) {
            return parseVariable();
        }
        throw std::runtime_error("Unexpected character: " + std::string(1, c));
    }
    
    std::shared_ptr<Inode> parseNumber() {
        skipWhitespace();
        size_t start = pos;
        while (pos < input.size() && (std::isdigit(input[pos]) || input[pos] == '.'))
            pos++;
        double value = std::stod(input.substr(start, pos - start));
        return std::make_shared<Value>(value);
    }
    
    std::shared_ptr<Inode> parseVariable() {
        skipWhitespace();
        size_t start = pos;
        while (pos < input.size() && std::isalnum(input[pos]))
            pos++;
        std::string varName = input.substr(start, pos - start);
        if (varTable.find(varName) == varTable.end())
            varTable[varName] = std::make_shared<Variable>(varName);
        return varTable[varName];
    }
};

int main() {
    std::cout << "Enter expression: ";
    std::string expression;
    std::getline(std::cin, expression);
    
    std::map<std::string, std::shared_ptr<Variable>> varTable;
    
    try {
        Parser parser(expression, varTable);
        auto tree = parser.parseExpression();
        std::cout << "Printed line: " << tree->print() << std::endl;
        std::cout << "Result: " << tree->calc() << std::endl;
    } catch (std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}
