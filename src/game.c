

#include <stdbool.h>

#include "game.h"
#include "screen.h"

#include <GL/glew.h>

SDL_Window *window;

void init(){
    window = create_window("CBlocky", 800, 480);
}

void loop(){
    bool quit = false;

    SDL_Event e;

    SDL_StartTextInput();

    while(!quit){
        while(SDL_PollEvent(&e) != 0){
            if(e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE){
                quit = true;
            }
        }

        render();

        SDL_GL_SwapWindow(window);
    }

    clean();
}

void render(){
    glViewport(0, 0, 800, 600);
    glClearColor(0.4f, 0.7f, 1.0f, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


}

void clean(){
    SDL_DestroyWindow(window);
    SDL_Quit();
}
