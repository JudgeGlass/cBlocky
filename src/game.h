

#ifndef CBLOCKY_GAME_H
#define CBLOCKY_GAME_H

#include <stdio.h>

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

#include "types.h"
#include "shader.h"
#include "chunk.h"

static void render();
static void clean();

void init();
void loop();

#endif //CBLOCKY_GAME_H
