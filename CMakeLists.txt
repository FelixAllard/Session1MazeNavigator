cmake_minimum_required(VERSION 4.0)
project(MazeProjectSherbrookeS1)

set(CMAKE_CXX_STANDARD 11)

add_library(MazeProjectSherbrookeS1 STATIC CppEntrypoint/main.cpp
        ArduinoMaze.c
        ArduinoMaze.h)
