cmake_minimum_required(VERSION 3.16)
project(cBlocky C)

set(CMAKE_C_STANDARD 11)

include_directories("/usr/local/include" "/opt/homebrew/include/" "/opt/homebrew/include/")
link_directories("/usr/local/lib" "/opt/homebrew/lib/" "/opt/homebrew/lib/")
LINK_LIBRARIES(SDL2main SDL2 GLEW "-framework OpenGL")

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
src/world.c
src/world.h
src/open-simplex-noise.c
src/open-simplex-noise.h
)
