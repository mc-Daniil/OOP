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

auto checkStringType(const int &input) -> bool;

auto checkChoice(const int &input) -> bool;

auto checkPath(const string &input) -> bool;

#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <type_traits>

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
