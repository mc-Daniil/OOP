#include <iostream>
#include <limits>
#include <type_traits>
#include <algorithm>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::runtime_error;
#define PROMPT "Choose function: 1, 2, 3, 4:"

#if defined(_WIN32) || defined(_WIN64)
const char PATH_SEPARATOR = '\\';
#elif defined(__APPLE__) || defined(__linux__)
const char PATH_SEPARATOR = '/';
#else
#error "Unsupported operating system"
#endif


template<typename T>
auto checkInput(const T &choice) -> bool{
    if constexpr (std::is_integral<T>::value) {
        return (choice <= 4 && choice >= 0);
    }
    else if constexpr (std::is_same<T, string>::value) {
        cout << "string" << endl;
        return true;
    }
    else {
        throw runtime_error("Unsupported type");
    }
}


template<typename T>
auto getInput(T &choice) -> bool{
    cout << PROMPT << endl;
    cin >> choice;
    if (cin.good() && checkInput(choice)) {
        return true;
    }
    if (cin.eof()) {
        throw runtime_error("Got EOF");
    }
    if (cin.bad()) {
        throw runtime_error("Got bad error");
    }
    if (cin.fail() || !checkInput(choice)) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cerr << "Wrong input. Try again" << endl;
    }
    return false;
}


auto join() -> string{
    return "";
}


auto absolute() -> string{
    cout << 2 << endl;
    return "";
}


auto relative() -> string{
    cout << 3 << endl;
    return "";
}


auto relativize() -> string{
    cout << 4 << endl;
    return "";
}


auto relativizeWrap() -> string{
    return "";
}


auto relativeWrap() -> string{
    return "";
}


auto absoluteWrap() -> string{
    return "";
}


auto joinWrap() -> string{
    return "";
}


auto finishWrap() -> string{
    return "Goodbye";
}


auto main() -> int {
    string (*funcs[5])() = {finishWrap, joinWrap, absoluteWrap, relativeWrap, relativizeWrap};
    try {
        int choice;
        while (!getInput(choice));
        funcs[choice]();
    }
    catch (const std::exception &e) {
        cerr << "Error:" << e.what() << endl;
    }
}