#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include "../src/model/Vector.h"

// Проверка конструктора по умолчанию
TEST_CASE("Vector: Default Constructor", "[Vector]") {
    Vector<int> vec;
    REQUIRE(vec.size() == 0);
    REQUIRE(vec.empty());
}

// Проверка конструктора с размером и значением
TEST_CASE("Vector: Constructor with size and value", "[Vector]") {
    Vector<int> vec(5, 42);
    REQUIRE(vec.size() == 5);
    for (size_t i = 0; i < vec.size(); ++i) {
        REQUIRE(vec[i] == 42);
    }
}

// Проверка push_back и доступа по индексу
TEST_CASE("Vector: push_back and access", "[Vector]") {
    Vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    REQUIRE(vec.size() == 3);
    REQUIRE(vec[0] == 1);
    REQUIRE(vec[1] == 2);
    REQUIRE(vec[2] == 3);
}

// Проверка emplace_back
TEST_CASE("Vector: emplace_back", "[Vector]") {
    struct TestStruct {
        int x;
        double y;

        TestStruct() : x(0), y(0.0) {} // Конструктор по умолчанию
        TestStruct(int a, double b) : x(a), y(b) {}
    };

    Vector <TestStruct> vec;
    vec.emplace_back(10, 3.14);
    vec.emplace_back(20, 2.71);

    REQUIRE(vec.size() == 2);
    REQUIRE(vec[0].x == 10);
    REQUIRE(vec[0].y == 3.14);
    REQUIRE(vec[1].x == 20);
    REQUIRE(vec[1].y == 2.71);
}

// Проверка вставки элемента в позицию
TEST_CASE("Vector: insert element", "[Vector]") {
    Vector<int> vec;
    vec.push_back(1);
    vec.push_back(3);

    auto it = vec.insert(vec.begin() + 1, 2);

    REQUIRE(vec.size() == 3);
    REQUIRE(*it == 2);
    REQUIRE(vec[0] == 1);
    REQUIRE(vec[1] == 2);
    REQUIRE(vec[2] == 3);
}

// Проверка удаления элемента по позиции (erase)
TEST_CASE("Vector: erase element", "[Vector]") {
    Vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    auto it = vec.erase(vec.begin() + 1); // Удаляем второй элемент

    REQUIRE(vec.size() == 2);
    REQUIRE(*it == 3);
    REQUIRE(vec[0] == 1);
    REQUIRE(vec[1] == 3);
}

// Проверка assign с диапазоном
TEST_CASE("Vector: assign range", "[Vector]") {
    std::vector<int> std_vec = {10, 20, 30, 40};
    Vector<int> vec;

    vec.assign(std_vec.begin(), std_vec.end());

    REQUIRE(vec.size() == 4);
    for (size_t i = 0; i < vec.size(); ++i) {
        REQUIRE(vec[i] == std_vec[i]);
    }
}

// Проверка итераторов (begin и end)
TEST_CASE("Vector: iterator support", "[Vector]") {
    Vector<int> vec = {1, 2, 3, 4};

    auto it = vec.begin();
    REQUIRE(*it == 1);
    ++it;
    REQUIRE(*it == 2);

    auto end_it = vec.end();
    REQUIRE(it != end_it);

    int sum = 0;
    for (auto x: vec) {
        sum += x;
    }
    REQUIRE(sum == 10); // 1 + 2 + 3 + 4 = 10
}

// Проверка clear
TEST_CASE("Vector: clear method", "[Vector]") {
    Vector<int> vec = {1, 2, 3, 4};
    REQUIRE(vec.size() == 4);

    vec.clear();
    REQUIRE(vec.size() == 0);
    REQUIRE(vec.empty());
}

// Проверка front и back
TEST_CASE("Vector: front and back access", "[Vector]") {
    Vector<int> vec = {1, 2, 3};

    REQUIRE(vec.front() == 1);
    REQUIRE(vec.back() == 3);
}

// Проверка pop_back
TEST_CASE("Vector: pop_back method", "[Vector]") {
    Vector<int> vec = {1, 2, 3};
    vec.pop_back();

    REQUIRE(vec.size() == 2);
    REQUIRE(vec.back() == 2);
}
