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
#define PROMPT "Enter:"

#if defined(_WIN32) || defined(_WIN64)
const char PATH_SEPARATOR = '\\';
#elif defined(__APPLE__) || defined(__linux__)
const char PATH_SEPARATOR = '/';
#else
#error "Unsupported operating system"
#endif


bool checkInput(const int &input) {
    return (4 >= input && input >= 0);
}


bool checkInput(const std::string &input) {
    return true;
}


template<typename T>
bool checkInput(const T &input) {
    throw runtime_error("Unsupported type");
}


template<typename T>
auto getInput(T &input) -> bool {
    cout << PROMPT << endl;
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


auto join(string &absolute, string &relative) -> string {
    if (relative.empty() || relative[0] == PATH_SEPARATOR) {
        throw std::invalid_argument("Not relative");
    }

    string result;
    if (absolute.back() == PATH_SEPARATOR) {
        result = absolute + relative;
    } else {
        result = absolute + PATH_SEPARATOR + relative;
    }
    return result;
}


auto absolute() -> string {
    cout << 2 << endl;
    return "";
}


auto relative() -> string {
    cout << 3 << endl;
    return "";
}


auto relativize() -> string {
    cout << 4 << endl;
    return "";
}


auto relativizeWrap() -> string {
    return "";
}


auto relativeWrap() -> string {
    return "";
}


auto absoluteWrap() -> string {
    return "";
}


auto joinWrap() -> string {
    string absolute;
    string relative;
    getInput(absolute);
    getInput(relative);
    return join(absolute, relative);
}


auto finishWrap() -> string {
    return "Goodbye";
}


auto main() -> int {
    string(*funcs[5])() = {finishWrap, joinWrap, absoluteWrap, relativeWrap, relativizeWrap};
    try {
        int choice;
        while (!getInput(choice));
        cout << funcs[choice]() << endl;
    }
    catch (const std::exception &e) {
        cerr << "Error:" << e.what() << endl;
    }
}