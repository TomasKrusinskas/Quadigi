#ifndef OPERATORS_H
#define OPERATORS_H

#include "Inode.h"
#include <memory>
#include <stdexcept>
#include <string>

class Sum : public Inode {
    std::shared_ptr<Inode> left;
    std::shared_ptr<Inode> right;
public:
    Sum(std::shared_ptr<Inode> l, std::shared_ptr<Inode> r) : left(l), right(r) {}
    double calc() override { return left->calc() + right->calc(); }
    std::string print() override {
        return "(" + left->print() + " + " + right->print() + ")";
    }
};

class Subtract : public Inode {
    std::shared_ptr<Inode> left;
    std::shared_ptr<Inode> right;
public:
    Subtract(std::shared_ptr<Inode> l, std::shared_ptr<Inode> r) : left(l), right(r) {}
    double calc() override { return left->calc() - right->calc(); }
    std::string print() override {
        return "(" + left->print() + " - " + right->print() + ")";
    }
};

class Multiply : public Inode {
    std::shared_ptr<Inode> left;
    std::shared_ptr<Inode> right;
public:
    Multiply(std::shared_ptr<Inode> l, std::shared_ptr<Inode> r) : left(l), right(r) {}
    double calc() override { return left->calc() * right->calc(); }
    std::string print() override {
        return "(" + left->print() + " * " + right->print() + ")";
    }
};

class Divide : public Inode {
    std::shared_ptr<Inode> left;
    std::shared_ptr<Inode> right;
public:
    Divide(std::shared_ptr<Inode> l, std::shared_ptr<Inode> r) : left(l), right(r) {}
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

#endif
