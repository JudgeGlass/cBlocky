

#ifndef CBLOCKY_GAME_H
#define CBLOCKY_GAME_H

#include <stdio.h>

#ifndef STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#endif

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include <stdbool.h>

#include "screen.h"
#include "types.h"
#include "states.h"
#include "shader.h"
#include "world.h"
#include "camera.h"

static void render();
static void update();
static void clean();
static void load_textures();

void init();
void loop();

#endif //CBLOCKY_GAME_H
