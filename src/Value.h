#ifndef VALUE_H
#define VALUE_H

#include "Inode.h"
#include <string>

class Value : public Inode {
    double value;
public:
    explicit Value(double v) : value(v) {}
    double calc() override { return value; }
    std::string print() override { return std::to_string(value); }
};

#endif
