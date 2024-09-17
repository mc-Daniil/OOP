#ifndef LAB1_INPUT_H
#define LAB1_INPUT_H

#include "main.h"

bool checkInput(const int &input);

bool checkInput(const string &input);

template<typename T>
bool checkInput(const T &input);

template<typename T>
auto getInput(T &input, const string &prompt) -> bool;

#endif //LAB1_INPUT_H
