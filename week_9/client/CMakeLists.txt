cmake_minimum_required(VERSION 3.17)
project(client1)

set (CMAKE_VERBOSE_MAKEFILE 1)

set(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")
add_executable(client1 main.cpp)

target_link_libraries(client1 ${Boost_LIBRARIES} rt)