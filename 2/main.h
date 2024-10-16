/**
 * @file main.h
 * @brief Dialog with user and starting functions for classes
 */
#ifndef INC_2_MAIN_H
#define INC_2_MAIN_H

#include <iostream>

/**
 * @brief Gets choice from user, starts needed function and works with exceptions
 */
auto main() -> int;

/**
 * @brief Prints "Goodbye to user"
 */
auto finish() -> void;

/**
 * @brief Adds new cocktail in cocktail table
 * 1. Gets cocktail name
 * 2. Gets volume
 * 3. If water, alcohol is 0%, else gets alcohol
 * 4. Creates cocktail
 * 5. Prints information about cocktail
 * 6. Adds in cocktail table
 */
auto addNew() -> void;


#endif //INC_2_MAIN_H
