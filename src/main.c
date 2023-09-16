#define SDL_MAIN_HANDLED

#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>

#include "screen.h"


int main(int argc, char *argv[]) {
    bool quit = false;

    create_window("cBlocky", 800, 480);

    SDL_Event e;

    SDL_StartTextInput();

    while(!quit){
        while(SDL_PollEvent(&e) != 0){
            if(e.type == SDL_QUIT){
                quit = true;
            }
        }

        SDL_GL_SwapWindow(window);
    }

    return 0;
}
