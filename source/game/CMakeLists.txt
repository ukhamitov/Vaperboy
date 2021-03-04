cmake_minimum_required(VERSION 3.17)
project(game)

set(CMAKE_CXX_STANDARD 17)

#include blah
add_subdirectory(../libs/blah blah)

add_library(game
        game.h
        game.cpp)

# Reference blah
target_link_libraries(game blah)