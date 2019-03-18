cmake_minimum_required(VERSION 3.13)
project(testproj)

SET(CMAKE_CXX_FLAGS -pthread)
set(CMAKE_CXX_STANDARD 14)

add_executable(testproj main.cpp test.h)