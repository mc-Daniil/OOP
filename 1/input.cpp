#include "input.h"

auto checkStringType(const int &input) -> bool {
    return (4 >= input && input >= 0);
}

auto checkChoice(const int &input) -> bool {
    return (4 >= input && input >= 0);
}

auto checkPath(const string &input) -> bool {
    if (input.empty()) {
        return false;
    }
    return true;
}
