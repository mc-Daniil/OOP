#ifndef LAB1_FILES_H
#define LAB1_FILES_H

#include "main.h"

auto join(string &absolute, string &relative) -> string;
auto absolute(string &relative) -> string;
auto relative(const std::string &absolute) -> string;
auto relativize(const string &base, const string &target) -> string;
auto relativizeWrap() -> string;
auto relativeWrap() -> string;
auto absoluteWrap() -> string;
auto joinWrap() -> string;
auto finishWrap() -> string;

#endif //LAB1_FILES_H
