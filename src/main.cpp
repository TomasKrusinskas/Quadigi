#include <iostream>
#include <string>
#include <map>
#include <memory>
#include "Parser.h"
#include "Variable.h"

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
    }
    catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}
