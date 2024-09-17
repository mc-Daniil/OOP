#include <iostream>
#include <limits>
#include <algorithm>
#include <filesystem>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::runtime_error;

#define PROMPT1 "Enter: 0 - exit\n1 - join\n2 - absolute\n3 - relative\n4 - relativize"
#define PROMPT2 "Enter path: "

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
auto getInput(T &input, const string& prompt) -> bool {
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


auto absolute(string &relative) -> string {
    std::filesystem::path p(relative);
    return std::filesystem::absolute(p).string();
}


auto relative(const std::string& absolute) -> string {
    string res; // Результат работы

    std::filesystem::path current_path = std::filesystem::current_path();
    std::filesystem::path target(absolute);

    if (target.is_relative()) {
        res = absolute;
    }

    // Проверка, является ли текущий каталог частью пути
    if (target.string().find(current_path.string()) == 0) {
        std::filesystem::path relative_path = std::filesystem::relative(target, current_path);
        res = relative_path.string();
    } else {
        // Вычисляем количество переходов в родительский каталог
        std::filesystem::path parent = current_path;
        int parent_steps = 0;

        while (parent != parent.root_path()) {
            parent = parent.parent_path();
            parent_steps++;
            if (target.string().find(parent.string()) == 0) {
                break;
            }
        }

        std::string relative_path = std::string(parent_steps * 2, '.') + "\\";
        std::filesystem::path target_relative = std::filesystem::relative(target, parent);
        relative_path += target_relative.string();
        res = relative_path;
    }
    return res;
}


auto relativize(const string& base, const string& target) -> string{
    std::filesystem::path base_path(base);
    std::filesystem::path target_path(target);

    // Оба ли абсолютные
    if (!base_path.is_absolute() || !target_path.is_absolute()) {
        throw std::invalid_argument("Both paths must be absolute.");
    }

    // Путь - подкаталог базового пути
    if (target_path.string().find(base_path.string()) != 0) {
        throw std::invalid_argument("Target path is not relative to the base path.");
    }

    // Вычисление относительного пути
    std::filesystem::path relative_path = std::filesystem::relative(target_path, base_path);
    return relative_path.string();
}


auto relativizeWrap() -> string {
    string absolute1;
    string absolute2;
    getInput(absolute1, PROMPT2);
    getInput(absolute2, PROMPT2);
    return relativize(absolute1, absolute2);
}


auto relativeWrap() -> string {
    string absolute;
    getInput(absolute, PROMPT2);
    return relative(absolute);
}


auto absoluteWrap() -> string {
    string relative;
    getInput(relative, PROMPT2);
    return absolute(relative);
}


auto joinWrap() -> string {
    string absolute;
    string relative;
    getInput(absolute, PROMPT2);
    getInput(relative, PROMPT2);
    return join(absolute, relative);
}


auto finishWrap() -> string {
    return "Goodbye";
}


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