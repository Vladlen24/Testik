cmake_minimum_required(VERSION 3.19)
project(week_11)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(week_11 main.cpp)

target_link_libraries(week_11 sfml-graphics sfml-audio)