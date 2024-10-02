cmake_minimum_required(VERSION 3.29)
project(lab2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

add_subdirectory(cocktail)

add_executable(main main.cpp main.h)

target_link_libraries(main cocktail)