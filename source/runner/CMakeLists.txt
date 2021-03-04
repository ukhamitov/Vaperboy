cmake_minimum_required(VERSION 3.17)
project(runner)

set(CMAKE_CXX_STANDARD 17)

#include blah
add_subdirectory(../game game)

add_executable(runner main.cpp)

# Reference game
target_link_libraries(runner game)