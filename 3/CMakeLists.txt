cmake_minimum_required(VERSION 3.22)
project(lab3)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

add_executable(main main.cpp main.h src/model/Map.cpp
        src/model/Cell.cpp
        src/model/Module.h
        src/model/Module.cpp
        src/model/NetworkModule.h
        src/model/NetworkModule.cpp
        src/model/SensorModule.h
        src/model/SensorModule.cpp
        src/model/Platform.h
        src/model/Platform.cpp
        src/model/StationaryPlatform.h
        src/model/StationaryPlatform.cpp
        src/model/MobilePlatform.h
        src/model/MobilePlatform.cpp)