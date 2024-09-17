#include "main.h"
#include "files.h"
#include "input.h"

auto main() -> int {
    string(*funcs[5])() = {finishWrap, joinWrap, absoluteWrap, relativeWrap, relativizeWrap};
    try {
        int choice;
        while (!getInput(choice, PROMPT1));
        cout << funcs[choice]() << endl;
    }
    catch (const std::exception &e) {
        cerr << "Error:" << e.what() << endl;
    }
}