cmake_minimum_required(VERSION 3.16)
project(cBlocky C)

set(CMAKE_C_STANDARD 11)

LINK_LIBRARIES(SDL2main SDL2 GLEW GL GLU -lm)

add_executable(cBlocky 
src/main.c 
src/screen.c 
src/screen.h 
src/game.c 
src/game.h
src/mesh.c
src/mesh.h
src/shader.c
src/shader.h
src/block.c
src/block.h
src/chunk.c
src/chunk.h
src/texture.h
src/texture.c
src/camera.h
src/camera.c
)
