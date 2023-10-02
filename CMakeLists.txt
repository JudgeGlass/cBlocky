cmake_minimum_required(VERSION 3.20)
project(cBlocky C)

set(CMAKE_C_STANDARD 11)

LINK_LIBRARIES(SDL2main SDL2 GLEW GL GLU)

add_executable(cBlocky src/main.c src/screen.c src/screen.h src/game.c src/game.h)
