cmake_minimum_required(VERSION 3.17)
project(lesson_7)

set(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_FLAGS -pthread)

add_executable(lesson_7 task1.cpp)