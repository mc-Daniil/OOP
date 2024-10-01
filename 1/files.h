/**
 * \file
 * \brief File with filesystem functions
 *
 * This file consists on functions and wraps for these functions for my filesystem
 */


#ifndef LAB1_FILES_H
#define LAB1_FILES_H

#include "main.h"

using std::string;

/**
 * \brief Concatenate absolute and relative path
 *
 * This function gets absolute and relative path, checks if relative path is relative and concatenates them
 * \param absolute - absolute path (std::string)
 * \param relative - relative path (std::string)
 * \return absolute + relative path
 */
auto join(const string &absolute, const string &relative) -> string;

/**
 * \brief Get absolute path from relative
 *
 * This function gets relative path from user
 * \param relative - relative path (std::string)
 * \return absolute path
 */
auto absolute(const string &relative) -> string;

/**
 * \brief Get relative path from absolute
 *
 * This function gets absolute path from user, checks if it's absolute, if relative in absolute, returns absolute, if not, adds ".." to relative path
 * \param absolute - absolute path (std::string)
 * \return relative path
 */
auto relative(const std::string &absolute) -> string;

/**
 * \brief Returns the location of the second path relative to the first
 *
 * This function gets 2 paths from user, checks if they are absolute and if first not in second and returns the location of the second path relative to the first
 * \param base - first path (std::string)
 * \param target - second path (std::string)
 * \return The location of the second path relative to the first
 */
auto relativize(const string &base, const string &target) -> string;

/**
 * \brief Wrap for relativize, inputs std::string
 * \return Result of relativize() with 2 std::string
 */
auto relativizeStringWrap() -> string;

/**
 * \brief Wrap for relative, inputs std::string
 * \return Result of relative() with std::string
 */
auto relativeStringWrap() -> string;

/**
 * \brief Wrap for absolute(), inputs std::string
 * \return Result of absolute() with std::string
 */
auto absoluteStringWrap() -> string;

/**
 * \brief Wrap for join(), inputs std::string
 * \return Result of join() with std::string
 */
auto joinStringWrap() -> string;

/**
 * \brief Prints "Goodbye"
 * \return Goodbye-string
 */
auto finishWrap() -> string;

/**
 * \brief Concatenate absolute and relative path
 *
 * This function gets absolute and relative path, checks if relative path is relative and concatenates them
 * \param absolute - absolute path (char*)
 * \param relative - relative path (char*)
 * @return absolute + relative path
 */
auto join(const char *absolute, const char *relative) -> string;

/**
 * \brief Get absolute path from relative
 *
 * This function gets relative path from user
 * \param relative - relative path (char*)
 * \return absolute path
 */
auto absolute(const char *relative) -> string;

/**
 * \brief Get relative path from absolute
 *
 * This function gets absolute path from user, checks if it's absolute, if relative in absolute, returns absolute, if not, adds ".." to relative path
 * \param absolute - absolute path (char*)
 * \return relative path
 */
auto relative(const char *absolute) -> string;

/**
 * \brief Returns the location of the second path relative to the first
 *
 * This function gets 2 paths from user, checks if they are absolute and if first not in second and returns the location of the second path relative to the first
 * \param base - first path (char*)
 * \param target - second path (char*)
 * \return The location of the second path relative to the first
 */
auto relativize(const char *base, const char *target) -> string;

/**
 * \brief Wrap for relativize, inputs char*
 * \return Result of relativize() with 2 char*
 */
auto relativizeCharWrap() -> string;

/**
 * \brief Wrap for relative, inputs char*
 * \return Result of relative() with char*
 */
auto relativeCharWrap() -> string;

/**
 * \brief Wrap for absolute(), inputs char*
 * \return Result of absolute() with char*
 */
auto absoluteCharWrap() -> string;

/**
 * \brief Wrap for join(), inputs char*
 * \return Result of join() with char*
 */
auto joinCharWrap() -> string;

#endif //LAB1_FILES_H
