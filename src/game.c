

#include <stdbool.h>

#include "game.h"
#include "screen.h"

#include <GL/glew.h>

SDL_Window *window;

u32 program_id;

mesh_t test_mesh;

void init(){
    window = create_window("CBlocky", 800, 480);

    load_shader(&program_id);

    glGenVertexArrays(1, &test_mesh.VAO);
    glGenBuffers(1, &test_mesh.VBO);

    glBindVertexArray(test_mesh.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, test_mesh.VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(f32) * 18 * 6, cube_vertex_front, GL_STATIC_DRAW);
    glBindVertexArray(0);

    test_mesh.vertex_count = 18 * 6;
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

    glUseProgram(program_id);

    draw_mesh(&test_mesh);
}

void clean(){
    SDL_DestroyWindow(window);
    SDL_Quit();
}
