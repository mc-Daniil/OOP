#include "input.h"

auto checkStringType(const int &input) -> bool {
    return (input >= 0 && input <= 2);
}

auto checkChoice(const int &input) -> bool {
    return (4 >= input && input >= 0);
}

auto checkPath(const string &input) -> bool {
    if (input.empty() || input.find(BAD_SEPARATOR) != string::npos) {
        return false;
    }
    return true;
}
