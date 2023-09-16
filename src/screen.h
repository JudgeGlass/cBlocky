

#ifndef CBLOCKY_SCREEN_H
#define CBLOCKY_SCREEN_H

#include <stdio.h>

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <gl/glu.h>
#include <SDL2/SDL_opengl.h>

static SDL_GLContext  create_gl_context(SDL_Window *window);

SDL_Window* create_window(const char* title, const uint16_t width, const uint16_t height);

#endif
