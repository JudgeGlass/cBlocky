

#include <stdbool.h>

#include "game.h"
#include "screen.h"

#include <GL/glew.h>

SDL_Window *window;

u32 program_id;
u32 texture_id;
chunk_t test_chunk;

void init(){
    window = create_window("CBlocky", 800, 480);

    program_id = load_shader();
    load_textures();

    init_chunk(&test_chunk, 0, 0);
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

void load_textures(){
    i32 width, height, nrChannels;
    u8 *data = stbi_load("res/atlas.png", &width, &height, &nrChannels, 0);
    if(!data){
        printf("Failed to load texture!\n");
        exit(-1);
    }

    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glEnable(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );

    GLfloat anisotropy;
    glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &anisotropy);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, anisotropy);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
}

void render(){
    glViewport(0, 0, 800, 600);
    glClearColor(0.4f, 0.7f, 1.0f, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(program_id);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    draw_chunk(&test_chunk, texture_id);
}

void clean(){
    SDL_DestroyWindow(window);
    SDL_Quit();
}
