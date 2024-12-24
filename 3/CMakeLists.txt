cmake_minimum_required(VERSION 3.22)
project(lab3)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавляем флаги для компиляции  -fsanitize=thread
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")

add_subdirectory(src/model)

add_executable(main main.cpp main.h src/ui/map_process.cpp)
target_link_libraries(main PRIVATE lib)

# sanitizers

#target_compile_options(main PRIVATE -fsanitize=thread)
#target_link_libraries(main PRIVATE -fsanitize=thread)

#find_package(Catch2 CONFIG REQUIRED)
#add_executable(tests_executable tests/tests_vector.cpp)
#target_link_libraries(tests_executable PRIVATE Catch2::Catch2 Catch2::Catch2WithMain)
