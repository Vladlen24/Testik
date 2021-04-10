cmake_minimum_required(VERSION 3.17)
project(week_7)

set (CMAKE_VERBOSE_MAKEFILE 1)

set(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")
add_executable(week_7 test.cpp)

target_link_libraries(week_7 ${Boost_LIBRARIES} rt)
