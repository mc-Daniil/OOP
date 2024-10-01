#include <catch.hpp>
#include "input.h"
#include "files.h"

TEST_CASE("checkStringType") {
    REQUIRE(checkStringType(0) == true);
    REQUIRE(checkStringType(1) == true);
    REQUIRE(checkStringType(2) == true);

    REQUIRE(checkStringType(-1) == false);
    REQUIRE(checkStringType(3) == false);
}

TEST_CASE("checkChoice") {
    REQUIRE(checkChoice(0) == true);
    REQUIRE(checkChoice(1) == true);
    REQUIRE(checkChoice(2) == true);
    REQUIRE(checkChoice(3) == true);
    REQUIRE(checkChoice(4) == true);

    REQUIRE(checkChoice(-1) == false);
    REQUIRE(checkChoice(5) == false);
}

TEST_CASE("checkPath") {
    REQUIRE(checkPath(std::string("valid\\path")) == true);
    REQUIRE(checkPath(std::string("another\\valid\\path")) == true);
    REQUIRE(checkPath("valid\\path") == true);
    REQUIRE(checkPath("another\\valid\\path") == true);

    REQUIRE(checkPath("") == false);
    REQUIRE(checkPath("invalid\\path\\:") == false);
    REQUIRE(checkPath("invalid\\path\\*") == false);
    REQUIRE(checkPath("invalid\\path\\|") == false);
}

TEST_CASE("join function") {
    // Проверка с std::string
    REQUIRE(join(std::string("D:\\code\\folder"), std::string("file.txt")) == "D:\\code\\folder\\file.txt");
    REQUIRE(join(std::string("D:\\code\\folder\\"), std::string("file.txt")) == "D:\\code\\folder\\file.txt");

    REQUIRE_THROWS_AS(join(std::string("D:\\code\\folder"), std::string("")), std::invalid_argument);
    REQUIRE_THROWS_AS(join(std::string("D:\\code\\folder"), std::string("\\file.txt")), std::invalid_argument);
    REQUIRE_THROWS_AS(join(std::string("D:\\code\\folder"), ""), std::invalid_argument);

    // Проверка с const char*
    REQUIRE(join("D:\\code\\folder", "file.txt") == "D:\\code\\folder\\file.txt");
    REQUIRE(join("D:\\code\\folder\\", "file.txt") == "D:\\code\\folder\\file.txt");

    REQUIRE_THROWS_AS(join("D:\\code\\folder", ""), std::invalid_argument);
    REQUIRE_THROWS_AS(join("D:\\code\\folder", "\\file.txt"), std::invalid_argument);
    REQUIRE_THROWS_AS(join("D:\\code\\folder", nullptr), std::invalid_argument);
}

TEST_CASE("absolute function") {
    auto current_path = std::filesystem::current_path().string();

    // Проверка с std::string
    REQUIRE(absolute(std::string("file.txt")).starts_with(current_path + "\\"));
    REQUIRE(absolute(std::string("subfolder\\file.txt")).starts_with(current_path + "\\subfolder"));
    REQUIRE(absolute(std::string("C:\\file.txt")) == "C:\\file.txt");

    // Проверка с const char*
    REQUIRE(absolute("file.txt").starts_with(current_path + "\\"));
    REQUIRE(absolute("subfolder\\file.txt").starts_with(current_path + "\\subfolder"));
    REQUIRE(absolute("C:\\file.txt") == "C:\\file.txt");
}

TEST_CASE("relative function") {
    auto current_path = std::filesystem::current_path().string();

    // Проверка с std::string
    REQUIRE(relative(std::string(current_path + "\\file.txt")) == "file.txt");
    REQUIRE(relative(std::string(current_path + "\\subfolder\\file.txt")).starts_with("subfolder"));
    REQUIRE(relative(std::string("C:\\folder\\file.txt")).find("..") != std::string::npos);

    // Проверка с const char*
    REQUIRE(relative(current_path + "\\file.txt") == "file.txt");
    REQUIRE(relative(current_path + "\\subfolder\\file.txt").starts_with("subfolder"));
    REQUIRE(relative("C:\\folder\\file.txt").find("..") != std::string::npos);
}

TEST_CASE("relativize function") {
    // Проверка с std::string
    REQUIRE(relativize(std::string("D:\\code\\folder"), std::string("D:\\code\\folder\\file.txt")) == "file.txt");
    REQUIRE_THROWS_AS(relativize(std::string("D:\\code\\folder"), std::string("E:\\folder\\file.txt")), std::invalid_argument);
    REQUIRE_THROWS_AS(relativize(std::string("D:\\code\\folder"), std::string("D:\\code\\other\\file.txt")), std::invalid_argument);

    // Проверка с const char*
    REQUIRE(relativize("D:\\code\\folder", "D:\\code\\folder\\file.txt") == "file.txt");
    REQUIRE_THROWS_AS(relativize("D:\\code\\folder", "E:\\folder\\file.txt"), std::invalid_argument);
    REQUIRE_THROWS_AS(relativize("D:\\code\\folder", "D:\\code\\other\\file.txt"), std::invalid_argument);
}

TEST_CASE("absolute with root directory") {
    REQUIRE(absolute("C:\\") == "C:\\");
    REQUIRE(absolute("D:\\") == "D:\\");
}

TEST_CASE("relative paths at different levels") {
    auto current_path = std::filesystem::current_path().string();
    REQUIRE(relative(std::string(current_path + "\\folder1\\folder2\\file.txt")).find("..") == std::string::npos);
    REQUIRE(relative("C:\\folder1\\folder2\\file.txt").find("..") != std::string::npos);
}
