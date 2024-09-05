#include <iostream>
#include <limits>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::runtime_error;
#define PROMPT "Choose function: 1, 2, 3, 4:"


auto checkInp(int &choice) -> bool{
    if (choice < 0 || choice > 4) {
        return false;
    }
    return true;
}


auto getChoice(int &choice) -> bool{
    cout << PROMPT << endl;
    cin >> choice;
    if (cin.good() && checkInp(choice)) {
        return true;
    }
    if (cin.eof()) {
        throw runtime_error("Got EOF");
    }
    if (cin.bad()) {
        throw runtime_error("Got bad error");
    }
    if (cin.fail() || !checkInp(choice)) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cerr << "Wrong input. Try again" << endl;
    }
    return false;
}


auto join() -> bool{
    cout << 1 << endl;
    return true;
}


auto absolute() -> bool{
    cout << 2 << endl;
    return true;
}


auto relative() -> bool{
    cout << 3 << endl;
    return true;
}


auto relativize() -> bool{
    cout << 4 << endl;
    return true;
}


auto finish() -> bool{
    cout << 0 << endl;
    return true;
}


auto main() -> int {
    bool (*funcs[5])() = {finish, join, absolute, relative, relativize};
    try {
        int choice;
        while (!getChoice(choice));
        funcs[choice]();
    }
    catch (const std::exception &e) {
        cerr << "Error:" << e.what() << endl;
    }
}