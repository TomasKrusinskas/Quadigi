#ifndef INODE_H
#define INODE_H

#include <string>

class Inode {
public:
    virtual ~Inode() {}
    virtual double calc() = 0;
    virtual std::string print() = 0;
};

#endif
