#include "input.h"


bool checkInput(const int &input) {
    return (4 >= input && input >= 0);
}


bool checkInput(const string &input) {
    if (input.empty()) {
        return false;
    }
    return true;
}


template<typename T>
bool checkInput(const T &input) {
    throw runtime_error("Unsupported type");
}


template<typename T>
auto getInput(T &input, const string &prompt) {
    cout << prompt << endl;
    cin >> input;
    if (cin.good() && checkInput(input)) {
        return true;
    }
    if (cin.eof()) {
        throw runtime_error("Got EOF");
    }
    if (cin.bad()) {
        throw runtime_error("Got bad error");
    }
    if (cin.fail() || !checkInput(input)) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cerr << "Wrong input. Try again" << endl;
    }
    return false;
}