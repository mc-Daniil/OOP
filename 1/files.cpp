#include "files.h"
#include "input.h"
#include <stdexcept>
#include <cstring>

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


auto absolute(const string &relative) -> string {
    std::filesystem::path p(relative);
    return std::filesystem::absolute(p).string();
}


auto relative(const string &absolute) -> string {
    string res;
    std::filesystem::path current_path = std::filesystem::current_path();
    std::filesystem::path target(absolute);

    if (target.is_relative()) {
        res = absolute;
        return res;
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

        string relative_path = string(parent_steps * 2, '.') + "\\";
        std::filesystem::path target_relative = std::filesystem::relative(target, parent);
        relative_path += target_relative.string();
        res = relative_path;
    }
    return res;
}


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


auto relativizeStringWrap() -> string {
    string absolute1;
    string absolute2;
    while (!getInput(absolute1, F_ABS_PATH) || !checkPath(absolute1));
    while (!getInput(absolute2, S_ABS_PATH) || !checkPath(absolute2));
    return relativize(absolute1, absolute2);
}


auto relativeStringWrap() -> string {
    string absolute;
    while (!getInput(absolute, ABS_PATH) || !checkPath(absolute));
    return relative(absolute);
}


auto absoluteStringWrap() -> string {
    string relative;
    while (!getInput(relative, REL_PATH) || !checkPath(relative));
    return absolute(relative);
}


auto joinStringWrap() -> string {
    string absolute;
    string relative;
    while (!getInput(absolute, ABS_PATH) || !checkPath(absolute));
    while (!getInput(relative, REL_PATH) || !checkPath(relative));
    return join(absolute, relative);
}


auto finishWrap() -> string {
    return "Goodbye";
}


auto join(const char *absolute, const char *relative) -> string {
    if (relative == nullptr || relative[0] == '\0' || relative[0] == PATH_SEPARATOR) {
        throw std::invalid_argument("Not relative");
    }

    string result;
    if (absolute[strlen(absolute) - 1] == PATH_SEPARATOR) {
        result = string(absolute) + relative;
    } else {
        result = string(absolute) + PATH_SEPARATOR + relative;
    }
    return result;
}


auto absolute(const char *relative) -> string {
    std::filesystem::path p(relative);
    return std::filesystem::absolute(p).string();
}

auto relative(const char *absolute) -> string {
    string res;

    std::filesystem::path current_path = std::filesystem::current_path();
    std::filesystem::path target(absolute);

    if (target.is_relative()) {
        res = absolute;
        return res;
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

        string relative_path = string(parent_steps * 2, '.') + "\\";
        std::filesystem::path target_relative = std::filesystem::relative(target, parent);
        relative_path += target_relative.string();
        res = relative_path;
    }
    return res;
}

auto relativize(const char *base, const char *target) -> string {
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


auto relativizeCharWrap() -> string {
    const char *absolute1;
    const char *absolute2;
    while (!getInput(absolute1, F_ABS_PATH) || !checkPath(absolute1));
    while (!getInput(absolute2, S_ABS_PATH) || !checkPath(absolute2));
    return relativize(absolute1, absolute2);
}


auto relativeCharWrap() -> string {
    const char *absolute;
    while (!getInput(absolute, ABS_PATH) || !checkPath(absolute));
    return relative(absolute);
}


auto absoluteCharWrap() -> string {
    const char *relative;
    while (!getInput(relative, REL_PATH) || !checkPath(relative));
    return absolute(relative);
}


auto joinCharWrap() -> string {
    const char *absolute;
    const char *relative;
    while (!getInput(absolute, ABS_PATH) || !checkPath(absolute));
    while (!getInput(relative, REL_PATH) || !checkPath(relative));
    return join(absolute, relative);
}