/**
 * \file
 * \brief File with functions that check input
 *
 * This file consists of functions that check input from user and return bool
 */


#ifndef LAB1_INPUT_H
#define LAB1_INPUT_H

#include "main.h"
#include <cstring>

using std::string;
using std::cin;
using std::cout;
using std::cerr;
using std::runtime_error;
using std::endl;
using std::numeric_limits;
using std::streamsize;

/**
 * Used to check string type: 1 - char*, 2 - string. 0 is used to exit
 * \param input - string type
 * \return True if input in [0, 2].
 */
auto checkStringType(const int &input) -> bool;

/**
 * Used to check function that user wants to use. 1 - join, 2 - absolute, 3 - relative, 4 - relativize
 * \param input - number of functions
 * \return True if input in [0, 4]
 */
auto checkChoice(const int &input) -> bool;

/**
 * Checks if inputted path is a path
 * \param input
 * \return True if path is a path
 */
auto checkPath(const string &input) -> bool;

#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <algorithm>
#include <ranges>

using namespace std;

template<typename T>
auto getInput(T &input, const string &prompt) -> bool {
    cout << prompt << endl;

    if constexpr (std::is_same_v<T, const char *>) {
        string temp;
        cin >> temp;

        if (cin.good()) {
            input = new char[temp.length() + 1];
            strcpy(const_cast<char *>(input), temp.c_str());
            return true;
        }
    } else {
        cin >> input;
        if (cin.good()) {
            return true;
        }
    }

    if (cin.eof()) {
        throw runtime_error("Got EOF");
    }
    if (cin.bad()) {
        throw runtime_error("Got bad error");
    }
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cerr << "Wrong input. Try again" << endl;
    }
    return false;
}


#endif //LAB1_INPUT_H
