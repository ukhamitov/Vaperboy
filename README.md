# Vaperboy

A small C++ 2D game which use [blah](https://github.com/NoelFB/blah) framework

#### building
- Requires C++17 and CMake 3.12+
- Platform Backend
    - [SDL2](https://github.com/NoelFB/blah/blob/master/src/internal/platform_backend_sdl2.cpp) can be enabled in CMake with `SDL2_ENABLED`, and setting `SDL2_INCLUDE_DIRS` and `SDL2_LIBRARIES`
- Graphics Backend
    - [OpenGL](https://github.com/NoelFB/blah/blob/master/src/internal/graphics_backend_gl.cpp) can be enabled in CMake with `OPENGL_ENABLED`.