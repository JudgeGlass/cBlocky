

#include "screen.h"

void create_window(const char* title, const uint16_t width, const uint16_t height){
    if(SDL_Init(SDL_INIT_EVERYTHING)){
        printf("Error: Could not init SDL!\n");
        exit(-1);
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_MASK);

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    if(window == NULL){
        printf("Failed to create window!\n");
        exit(-1);
    }

    glContext = SDL_GL_CreateContext(window);

    if(glContext == NULL){
        printf("Failed to create OpenGL context!\n");
        exit(-1);
    }

    if(glewInit() != GLEW_OK){
        printf("Failed to create GLEW context!\n");
        exit(-1);
    }

    SDL_GL_SetSwapInterval(1);
}

void init_gl(){

}
