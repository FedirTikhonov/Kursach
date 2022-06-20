cmake_minimum_required(VERSION 3.21)
project(testmkr)

set(CMAKE_CXX_STANDARD 14)

add_executable(testmkr main.cpp lib.h lib.cpp)
