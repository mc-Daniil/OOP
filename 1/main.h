#ifndef LAB1_MAIN_H
#define LAB1_MAIN_H

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

#endif //LAB1_MAIN_H
