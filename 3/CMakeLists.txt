cmake_minimum_required(VERSION 3.22)
project(lab3)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавляем флаги для компиляции  -fsanitize=thread
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -fsanitize=thread")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=thread")

add_subdirectory(src/model)
add_subdirectory(src/ui)

add_executable(main main.cpp main.h)

# sanitizers
target_compile_options(main PRIVATE -fsanitize=thread)
target_link_libraries(main PRIVATE -ldl)
target_link_libraries(main PRIVATE model ui)


set_target_properties(main PROPERTIES RUNTIME_OUTPUT_DIRECTORY /mnt/d/code/c++/b23516_rudakov.da/3/cmake-build-wsl/bin)
set_target_properties(model PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set_target_properties(ui PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)


#find_package(Catch2 CONFIG REQUIRED)
#add_executable(tests_executable tests/tests_vector.cpp)
#target_link_libraries(tests_executable PRIVATE Catch2::Catch2 Catch2::Catch2WithMain)
