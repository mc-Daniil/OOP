/**
 * @file main.h
 * @brief Dialog with user and starting functions for classes
 */
#ifndef INC_2_MAIN_H
#define INC_2_MAIN_H

#include <string>

const std::string PROMPT("Choose:\n\t0 - exit\n\t1 - add new cocktail\n\t2 - view cocktail\n\t3 - view table status\n\t4 - delete cocktail\n\t5 - get 500 ml of cocktail\n\t6 - get number of cocktails with %\n\t7 - rename cocktail\n\t8 - mix cocktails\n\t9 - pour the cocktail\n\t10 - increase volume n times\n>> ");
const std::string PROMPT_N("Enter n\n>> ");
const std::string PROMPT_NAME("Enter name of cocktail ('Water' if you want water):\n>> ");
const std::string PROMPT_OLD_NAME("Enter old name of cocktail ('Water' if you want water):\n>> ");
const std::string PROMPT_NEW_NAME("Enter new name of cocktail ('Water' if you want water):\n>> ");
const std::string PROMPT_FIRST_NAME("Enter name of cocktail 1 ('Water' if you want water):\n>> ");
const std::string PROMPT_SECOND_NAME("Enter name of cocktail 2 ('Water' if you want water):\n>> ");
const std::string PROMPT_ALCOHOL("Enter alcohol % of cocktail:\n>> ");
const std::string PROMPT_MIN_ALCOHOL("Enter minimum alcohol % of cocktail:\n>> ");
const std::string PROMPT_MAX_ALCOHOL("Enter maximum alcohol % of cocktail:\n>> ");
const std::string PROMPT_VOLUME("Enter volume of cocktail:\n>> ");

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
