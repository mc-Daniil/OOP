cmake_minimum_required(VERSION 3.22)
project(model_library)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Определяем библиотеку
add_library(model SHARED
        Map.cpp
        Map.h
        Cell.cpp
        Cell.h
        Intruder.h
        MobilePlatform.cpp
        MobilePlatform.h
        Module.cpp
        NetworkModule.cpp
        SensorModule.cpp
        StationaryPlatform.cpp
        WeaponModule.cpp
        Intruder.cpp
)

# Флаги компиляции
target_compile_options(model PRIVATE -fsanitize=thread)

# Флаги линковки
target_link_libraries(model PRIVATE -fsanitize=thread)

# Указываем директорию вывода библиотеки
set_target_properties(model PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Проверим, если библиотека скомпилирована и находится в нужной папке
message(STATUS "Library model will be created in: ${CMAKE_BINARY_DIR}/lib")
