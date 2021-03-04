cmake_minimum_required(VERSION 3.17)
project(game)

set(CMAKE_CXX_STANDARD 17)

#include blah
add_subdirectory(../libs/blah blah)

add_library(game
        game.h
        game.cpp
#        core/component.h
#        core/component.cpp
#        core/entity.h
#        core/entity.cpp
        core/world.h
        core/world.cpp
        core/transform.h
        components/timer.h
        components/timer.cpp
        )

# Reference blah
target_link_libraries(game blah)