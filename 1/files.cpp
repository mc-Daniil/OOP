/**
 * \file
 * \brief File with filesystem functions
 *
 * This file consists on functions and wraps for these functions for my filesystem
 */


#include "files.h"
#include "input.h"
#include <stdexcept>
#include <cstring>
/**
 * \brief Concatenate absolute and relative path
 *
 * This function gets absolute and relative path, checks if relative path is relative and concatenates them
 * \param absolute - absolute path (std::string)
 * \param relative - relative path (std::string)
 * @return absolute + relative path
 */
auto join(const string &absolute, const string &relative) -> string {
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

/**
 * \brief Get absolute path from relative
 *
 * This function gets relative path from user
 * \param relative - relative path (std::string)
 * \return absolute path
 */
auto absolute(const string &relative) -> string {
    std::filesystem::path p(relative);
    return std::filesystem::absolute(p).string();
}

/**
 * \brief Get relative path from absolute
 *
 * This function gets absolute path from user, checks if it's absolute, if relative in absolute, returns absolute, if not, adds ".." to relative path
 * \param absolute - absolute path (std::string)
 * \return relative path
 */
auto relative(const string &absolute) -> string {
    string res;
    std::filesystem::path current_path = std::filesystem::current_path();
    std::filesystem::path target(absolute);

    if (target.is_relative()) {
        res = absolute;
    }

    if (target.string().find(current_path.string()) == 0) {
        std::filesystem::path relative_path = std::filesystem::relative(target, current_path);
        res = relative_path.string();
    } else {
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

/**
 * \brief Returns the location of the second path relative to the first
 *
 * This function gets 2 paths from user, checks if they are absolute and if first not in second and returns the location of the second path relative to the first
 * \param base - first path (std::string)
 * \param target - second path (std::string)
 * \return The location of the second path relative to the first
 */
auto relativize(const string &base, const string &target) -> string {
    std::filesystem::path base_path(base);
    std::filesystem::path target_path(target);

    if (!base_path.is_absolute() || !target_path.is_absolute()) {
        throw std::invalid_argument("Both paths must be absolute.");
    }

    if (target_path.string().find(base_path.string()) != 0) {
        throw std::invalid_argument("Target path is not relative to the base path.");
    }

    std::filesystem::path relative_path = std::filesystem::relative(target_path, base_path);
    return relative_path.string();
}

/**
 * \brief Wrap for relativize, inputs std::string
 * \return Result of relativize() with 2 std::string
 */
auto relativizeStringWrap() -> string {
    string absolute1;
    string absolute2;
    while (!getInput(absolute1, F_ABS_PATH) || !checkPath(absolute1));
    while (!getInput(absolute2, S_ABS_PATH) || !checkPath(absolute2));
    return relativize(absolute1, absolute2);
}

/**
 * \brief Wrap for relative, inputs std::string
 * \return Result of relative() with std::string
 */
auto relativeStringWrap() -> string {
    string absolute;
    while (!getInput(absolute, ABS_PATH) || !checkPath(absolute));
    return relative(absolute);
}

/**
 * \brief Wrap for absolute(), inputs std::string
 * \return Result of absolute() with std::string
 */
auto absoluteStringWrap() -> string {
    string relative;
    while (!getInput(relative, REL_PATH) || !checkPath(relative));
    return absolute(relative);
}

/**
 * \brief Wrap for join(), inputs std::string
 * \return Result of join() with std::string
 */
auto joinStringWrap() -> string {
    string absolute;
    string relative;
    while (!getInput(absolute, ABS_PATH) || !checkPath(absolute));
    while (!getInput(relative, REL_PATH) || !checkPath(relative));
    return join(absolute, relative);
}

/**
 * \brief Prints "Goodbye"
 * \return Goodbye-string
 */
auto finishWrap() -> string {
    return "Goodbye";
}

/**
 * \brief Concatenate absolute and relative path
 *
 * This function gets absolute and relative path, checks if relative path is relative and concatenates them
 * \param absolute - absolute path (char*)
 * \param relative - relative path (char*)
 * @return absolute + relative path
 */
auto join(const char *absolute, const char *relative) -> string {
    if (relative == nullptr || relative[0] == '\0' || relative[0] == PATH_SEPARATOR) {
        throw std::invalid_argument("Not relative");
    }

    std::string result;
    if (absolute[strlen(absolute) - 1] == PATH_SEPARATOR) {
        result = std::string(absolute) + relative;
    } else {
        result = std::string(absolute) + PATH_SEPARATOR + relative;
    }
    return result;
}

/**
 * \brief Get absolute path from relative
 *
 * This function gets relative path from user
 * \param relative - relative path (char*)
 * \return absolute path
 */
auto absolute(const char *relative) -> string {
    std::filesystem::path p(relative);
    return std::filesystem::absolute(p).string();
}

/**
 * \brief Get relative path from absolute
 *
 * This function gets absolute path from user, checks if it's absolute, if relative in absolute, returns absolute, if not, adds ".." to relative path
 * \param absolute - absolute path (char*)
 * \return relative path
 */
auto relative(const char *absolute) -> std::string {
    std::string res;

    std::filesystem::path current_path = std::filesystem::current_path();
    std::filesystem::path target(absolute);

    if (target.is_relative()) {
        res = absolute;
    }

    if (target.string().find(current_path.string()) == 0) {
        std::filesystem::path relative_path = std::filesystem::relative(target, current_path);
        res = relative_path.string();
    } else {
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
/**
 * \brief Returns the location of the second path relative to the first
 *
 * This function gets 2 paths from user, checks if they are absolute and if first not in second and returns the location of the second path relative to the first
 * \param base - first path (char*)
 * \param target - second path (char*)
 * \return The location of the second path relative to the first
 */
auto relativize(const char *base, const char *target) -> std::string {
    std::filesystem::path base_path(base);
    std::filesystem::path target_path(target);

    if (!base_path.is_absolute() || !target_path.is_absolute()) {
        throw std::invalid_argument("Both paths must be absolute.");
    }

    if (target_path.string().find(base_path.string()) != 0) {
        throw std::invalid_argument("Target path is not relative to the base path.");
    }

    std::filesystem::path relative_path = std::filesystem::relative(target_path, base_path);
    return relative_path.string();
}

/**
 * \brief Wrap for relativize, inputs char*
 * \return Result of relativize() with 2 char*
 */
auto relativizeCharWrap() -> string {
    const char *absolute1;
    const char *absolute2;
    while (!getInput(absolute1, F_ABS_PATH) || !checkPath(absolute1));
    while (!getInput(absolute2, S_ABS_PATH) || !checkPath(absolute2));
    return relativize(absolute1, absolute2);
}

/**
 * \brief Wrap for relative, inputs char*
 * \return Result of relative() with char*
 */
auto relativeCharWrap() -> string {
    const char *absolute;
    while (!getInput(absolute, ABS_PATH) || !checkPath(absolute));
    return relative(absolute);
}

/**
 * \brief Wrap for absolute(), inputs char*
 * \return Result of absolute() with char*
 */
auto absoluteCharWrap() -> string {
    const char *relative;
    while (!getInput(relative, REL_PATH) || !checkPath(relative));
    return absolute(relative);
}

/**
 * \brief Wrap for join(), inputs char*
 * \return Result of join() with char*
 */
auto joinCharWrap() -> string {
    const char *absolute;
    const char *relative;
    while (!getInput(absolute, ABS_PATH) || !checkPath(absolute));
    while (!getInput(relative, REL_PATH) || !checkPath(relative));
    return join(absolute, relative);
}