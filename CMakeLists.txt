cmake_minimum_required(VERSION 3.25)
project(cBlocky C)

set(CMAKE_C_STANDARD 11)

LINK_LIBRARIES(SDL2main SDL2 glew32 opengl32 glu32)

add_executable(cBlocky src/main.c src/screen.c src/screen.h src/game.c src/game.h)
