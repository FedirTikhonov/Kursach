cmake_minimum_required(VERSION 3.21)
project(dstest)

set(CMAKE_CXX_STANDARD 14)

add_executable(dstest main.cpp newStack.h newQueue.h bstInt.cpp bstInt.h)
