

#include "screen.h"

SDL_Window* create_window(const char* title, const uint16_t width, const uint16_t height){
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("Error: Could not init SDL!\n");
        exit(-1);
    }

    SDL_Window *window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);

    if(window == NULL){
        printf("Failed to create window!\n");
        exit(-1);
    }

    SDL_GLContext gl_context = create_gl_context(window);

    if(gl_context == NULL){
        printf("Failed to create OpenGL context!\n");
        exit(-1);
    }

    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK){
        printf("Failed to create GLEW context!\n");
        exit(-1);
    }

    SDL_GL_SetSwapInterval(1);
    printf("Window and context created!\n");

    return window;
}

static SDL_GLContext  create_gl_context(SDL_Window *window){
#ifdef __arm__
    printf("ARM DETECTED: Using OpenGL ES 3.1\n");
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,SDL_GL_CONTEXT_PROFILE_ES);
#else
    printf("Using OpenGL 3.3 CORE\n");
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,SDL_GL_CONTEXT_PROFILE_CORE);
#endif

    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,4);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    // enable double buffering (should be on by default)
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    return SDL_GL_CreateContext(window);
}

