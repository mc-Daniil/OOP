cmake_minimum_required(VERSION 3.22)
project(ui_library)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(ui SHARED map_process.cpp map_process.h)

# Флаги компиляции
target_compile_options(ui PRIVATE -fsanitize=thread)

# Флаги линковки
target_link_libraries(ui PRIVATE -fsanitize=thread)

# Указываем директорию вывода библиотеки
set_target_properties(ui PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Проверим, если библиотека скомпилирована и находится в нужной папке
message(STATUS "Library ui will be created in: ${CMAKE_BINARY_DIR}/lib")
