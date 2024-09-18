#include "main.h"
#include "files.h"
#include "input.h"

auto main() -> int {
    string(*funcs[2][5])() = {{finishWrap, joinCharWrap, absoluteCharWrap, relativeCharWrap, relativizeCharWrap},
                              {finishWrap, joinStringWrap, absoluteStringWrap, relativeStringWrap,
                               relativizeStringWrap}};
    try {
        int typeString;
        while (!getInput(typeString, PROMPT3));
        int choice;
        while (!getInput(choice, PROMPT1));
        cout << funcs[typeString][choice]() << endl;
    }
    catch (const std::exception &e) {
        cerr << "Error:" << e.what() << endl;
    }
}