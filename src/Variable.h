#ifndef VARIABLE_H
#define VARIABLE_H

#include "Inode.h"
#include <iostream>
#include <string>

class Variable : public Inode {
    std::string name;
    double value;
    bool isSet;
public:
    explicit Variable(const std::string& n) : name(n), value(0.0), isSet(false) {}
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

#endif
