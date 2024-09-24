#ifndef LAB1_FILES_H
#define LAB1_FILES_H

#include "main.h"

using std::string;

auto join(const string &absolute, const string &relative) -> string;

auto absolute(const string &relative) -> string;

auto relative(const std::string &absolute) -> string;

auto relativize(const string &base, const string &target) -> string;

auto relativizeStringWrap() -> string;

auto relativeStringWrap() -> string;

auto absoluteStringWrap() -> string;

auto joinStringWrap() -> string;

auto finishWrap() -> string;

auto relativizeCharWrap() -> string;

auto relativeCharWrap() -> string;

auto absoluteCharWrap() -> string;

auto joinCharWrap() -> string;

#endif //LAB1_FILES_H
