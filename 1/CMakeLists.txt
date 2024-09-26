cmake_minimum_required(VERSION 3.16)
project(lab1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(input input.cpp input.h)
add_library(files files.cpp files.h)

add_executable(main main.cpp)

target_link_libraries(main PRIVATE input files)

target_compile_options(main PRIVATE -Wall -Wextra)

# mkdir build
# cd build
# cmake ..
# make
