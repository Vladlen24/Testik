cmake_minimum_required(VERSION 3.19)
project(particles)

set(CMAKE_CXX_STANDARD 20)

set(SFML_INCLUDE_DIR "/home/vladlen/Загрузки/SFML-2.5.1/include")
set(SFML_LIBRARY_DIR "/home/vladlen/Загрузки/SFML-2.5.1/lib")
set(SFML_DIR "/home/vladlen/Загрузки/SFML-2.5.1/lib/cmake/SFML")

link_directories(SFML_LIBRARY_DIR)
include_directories(SFML_INCLUDE_DIR)

find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)

if(SFML_FOUND)
    message(STATUS "SFML_INCLUDE_DIR: ${SFML_INCLUDE_DIR}")
    message(STATUS "SFML_LIBRARIES: ${SFML_LIBRARIES}")
    message(STATUS "SFML_VERSION: ${SFML_VERSION}")
endif()

add_executable(particles main.cpp functions.hpp link.hpp particle.hpp pressure.hpp system.hpp link.cpp particle.cpp pressure.cpp system.cpp)
target_link_libraries (particles sfml-graphics sfml-window sfml-system)