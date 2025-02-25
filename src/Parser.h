#ifndef PARSER_H
#define PARSER_H

#include "Inode.h"
#include "Value.h"
#include "Variable.h"
#include "Operators.h"
#include <string>
#include <map>
#include <memory>
#include <stdexcept>
#include <cctype>

class Parser {
    std::string input;
    size_t pos;
    std::map<std::string, std::shared_ptr<Variable>>& varTable;

    void skipWhitespace() {
        while (pos < input.size() && std::isspace(input[pos]))
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
    Parser(const std::string& in, std::map<std::string, std::shared_ptr<Variable>>& table)
        : input(in), pos(0), varTable(table) {
    }

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
            }
            else {
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
            }
            else {
                break;
            }
        }
        return node;
    }

    std::shared_ptr<Inode> parseFactor() {
        skipWhitespace();
        char c = peek();
        if (c == '(') {
            get(); // consume '('
            auto node = parseExpression();
            if (get() != ')')
                throw std::runtime_error("Expected ')'");
            return node;
        }
        else if (std::isdigit(c) || c == '.') {
            return parseNumber();
        }
        else if (std::isalpha(c)) {
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

#endif
