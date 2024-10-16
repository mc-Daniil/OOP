/**
 * @file io.h
 * @brief Consists of functions, that get input and check input
 */
#ifndef LAB2_IO_H
#define LAB2_IO_H

#include <iostream>
#include <limits>
#include "../main.h"

/**
 * @brief Gets input from user (all types)
 * @tparam T - template
 * @param input - input from user
 * @param prompt - prompt to print
 * @return true or false
 */
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

/**
 * Checks what user wants to do. 0 <= choice <= 7 (Only 8 functions)
 * @param choice - user choice (Number of function)
 * @return true or false
 */
auto checkChoice(int &choice) -> bool;

/**
 * Checks alcohol %. 0 <= alcohol <= 100
 * @param alcohol - alcohol % from user
 * @return true or false
 */
auto checkAlcohol(int &alcohol) -> bool;
/**
 * Checks volume of cocktail that user wants. It must be >= 0
 * @param volume - volume from user
 * @return true or false
 */
auto checkVolume(int &volume) -> bool;

#endif //LAB2_IO_H
