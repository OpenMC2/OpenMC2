cmake_minimum_required(VERSION 2.6)
project(OpenMC2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    src/UnkObjects/unk402560.hpp
    src/UnkObjects/unk5769E0.cpp
    src/UnkObjects/unk5769E0.hpp
    src/UnkObjects/unk600960.hpp
    src/UnkObjects/unk613360.hpp
    src/UnkObjects/unk6C2E88.hpp
    src/UnkObjects/unk6C3250.hpp
    src/UnkObjects/unk6C3890.hpp
    src/UnkObjects/unk8600F8.cpp
    src/UnkObjects/unk8600F8.hpp
    src/UnkObjects/unk86D28C.cpp
    src/UnkObjects/unk86D28C.hpp
    src/Addresses.hpp
    src/CommandLine.cpp
    src/CommandLine.hpp
    src/Game.cpp
    src/Game.hpp
    src/Logging.cpp
    src/Logging.hpp
    src/OpenMC2.cpp)

add_library(${PROJECT} SHARED ${SOURCE_FILES})