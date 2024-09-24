/**
 * \file
 * \brief File with functions that check input
 *
 * This file consists of functions that check input from user and return bool
 */

#include "input.h"
/**
 * Used to check string type: 1 - char*, 2 - string. 0 is used to exit
 * \param input - string type
 * \return True if input in [0, 2].
 */
auto checkStringType(const int &input) -> bool {
    return (input >= 0 && input <= 2);
}
/**
 * Used to check function that user wants to use. 1 - join, 2 - absolute, 3 - relative, 4 - relativize
 * \param input - number of functions
 * \return True if input in [0, 4]
 */
auto checkChoice(const int &input) -> bool {
    return (4 >= input && input >= 0);
}
/**
 * Checks if inputted path is a path
 * \param input
 * \return True if path is a path
 */
auto checkPath(const string &input) -> bool {
    if (input.empty() || input.find(BAD_SEPARATOR) != string::npos) {
        return false;
    }
    return true;
}
