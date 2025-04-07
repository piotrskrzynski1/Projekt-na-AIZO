cmake_minimum_required(VERSION 3.26)
project(projektaizofun)

set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_CXX_FLAGS_RELEASE "-Ofast -march=native -DNDEBUG")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--stack,67108864")
set(CMAKE_BUILD_TYPE Release)

add_executable(projektaizofun main.cpp
        ClassesAndHeaders/Timer.cpp
        ClassesAndHeaders/Timer.h
        ClassesAndHeaders/ArgumentHolder.cpp
        ClassesAndHeaders/ArgumentHolder.h
        ClassesAndHeaders/Utilities.hpp
        ClassesAndHeaders/FileReader.hpp
        ClassesAndHeaders/SortingAlgorithms.hpp
        ClassesAndHeaders/Vector.hpp
        ClassesAndHeaders/Includes.h
        ClassesAndHeaders/Tests.hpp
        ClassesAndHeaders/TestsUtilities.hpp
        ClassesAndHeaders/Game.hpp
        ClassesAndHeaders/Planszowka.hpp
)
