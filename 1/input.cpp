#include "input.h"


auto checkStringType(const int &input) -> bool {
    return (input >= 0 && input <= 2);
}


auto checkChoice(const int &input) -> bool {
    return (4 >= input && input >= 0);
}


auto checkPath(const std::string &input) -> bool {
    const std::string invalid_chars = ":\"<>|?*";

    if (input.empty()) {
        return false;
    }

    return std::ranges::all_of(input, [&invalid_chars](char c) {
        return invalid_chars.find(c) == std::string::npos;
    });
}

