#ifndef LAB2_IO_H
#define LAB2_IO_H

#include <iostream>
#include <limits>
#include "../main.h"

template<typename T>
auto getInput(T &input, const std::string &prompt) -> bool {
    std::cout << prompt;
    std::cin >> input;
    if (std::cin.good()) {
        return true;
    }
    if (std::cin.eof()) {
        throw std::runtime_error("EOF");
    }
    if (std::cin.bad()) {
        throw std::runtime_error("BAAAAAAAAD");
    }
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cerr << "Wrong input. Try again\n>> ";
    }
    return false;
}

auto checkChoice(int &choice) -> bool;

#endif //LAB2_IO_H
