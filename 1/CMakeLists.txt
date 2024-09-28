cmake_minimum_required(VERSION 3.16)
project(lab1)

# Указываем путь к toolchain для vcpkg
set(CMAKE_TOOLCHAIN_FILE "C:/Users/rudak/.vcpkg-clion/vcpkg/scripts/buildsystems/vcpkg.cmake")

# Устанавливаем стандарт C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Определяем библиотеки
add_library(input input.cpp input.h)
add_library(files files.cpp files.h)

# Определяем исполняемый файл main
add_executable(main main.cpp)
target_link_libraries(main PRIVATE input files)

# Добавляем параметры компиляции
target_compile_options(main PRIVATE -Wall -Wextra)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")

# Находим Catch2 для тестов
find_package(Catch2 CONFIG REQUIRED)

# Определяем исполняемый файл для тестов
add_executable(tests_executable tests.cpp)
target_link_libraries(tests_executable PRIVATE input files Catch2::Catch2 Catch2::Catch2WithMain)

# Включаем тестирование
enable_testing()

# Добавляем тесты
add_test(NAME tests COMMAND tests_executable)
