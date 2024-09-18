#ifndef LAB1_INPUT_H
#define LAB1_INPUT_H

#include "main.h"

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

template<typename T>
auto getInput(T &input, const string &prompt) -> bool {
    cout << prompt << endl;

    if constexpr (std::is_same_v<T, const char *>) {
        string temp;
        cin >> temp;
        if (cin.good()) {
            input = temp.c_str(); // Присваиваем `const char *`
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
