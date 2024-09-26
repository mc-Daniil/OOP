/**
 * \file
 * \brief Main file
 *
 * This file gets input from user: string type, number of function and calls wrap function
 */

#include "main.h"
#include "files.h"
#include "input.h"

/**
 * Main func
 * \return Returns return code
 */
auto main() -> int {
    string(*funcs[2][5])() = {{finishWrap, joinCharWrap,   absoluteCharWrap,   relativeCharWrap, relativizeCharWrap},
                              {finishWrap, joinStringWrap, absoluteStringWrap, relativeStringWrap,
                                                                                                 relativizeStringWrap}};
    try {
        int typeString;
        while (!getInput(typeString, STR_TYPE) || !checkStringType(typeString));
        if (typeString != 0) {
            int choice;
            while (!getInput(choice, CHOICE) || !checkChoice(choice));
            cout << funcs[typeString - 1][choice]() << endl;
        } else {
            cout << finishWrap() << endl;
        }
    }
    catch (const std::exception &e) {
        cerr << "Error:" << e.what() << endl;
    }
}