#ifndef LAB1_MAIN_H
#define LAB1_MAIN_H

#include <iostream>
#include <limits>
#include <algorithm>
#include <filesystem>
#include "files.h"
#include "input.h"

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::runtime_error;

#define CHOICE "Enter:\n0 - exit\n1 - join\n2 - absolute\n3 - relative\n4 - relativize"
#define ABS_PATH "Enter absolute path: "
#define REL_PATH "Enter relative path: "
#define F_ABS_PATH "Enter first absolute path: "
#define S_ABS_PATH "Enter second absolute path: "
#define STR_TYPE "Choose:\n0 - exit\n1 - char*\n2 - string"

#if defined(_WIN32) || defined(_WIN64)
const char PATH_SEPARATOR = '\\';
const char BAD_SEPARATOR = '/';
#elif defined(__APPLE__) || defined(__linux__)
const char PATH_SEPARATOR = '/';
const char BAD_SEPARATOR = '\\';
#else
#error "Unsupported operating system"
#endif

#endif //LAB1_MAIN_H
