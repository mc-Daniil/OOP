cmake_minimum_required(VERSION 3.22)
project(lab3)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra --coverage")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")

set(CMAKE_TOOLCHAIN_FILE "C:/Users/rudak/.vcpkg-clion/vcpkg/scripts/buildsystems/vcpkg.cmake")

add_executable(main main.cpp main.h src/model/Vector.h)
target_compile_options(main PRIVATE --coverage)

find_package(Catch2 CONFIG REQUIRED)
add_executable(tests_executable tests/tests_vector.cpp)
target_link_libraries(tests_executable PRIVATE Catch2::Catch2 Catch2::Catch2WithMain)
