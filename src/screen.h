

#ifndef CBLOCKY_SCREEN_H
#define CBLOCKY_SCREEN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <gl/glu.h>
#include <SDL2/SDL_opengl.h>

static SDL_Window *window;
static SDL_GLContext *glContext;

void create_window(const char* title, const uint16_t width, const uint16_t height);
void init_gl();

#endif
