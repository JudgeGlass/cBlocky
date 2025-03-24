#include "game.h"

SDL_Window *window;

u32 program_id;
u32 texture_id;
f64 delta_time;
world_t world;
camera_t camera;
game_states_t game_states;

void init()
{
    window = create_window("CBlocky", WINDOW_WIDTH, WINDOW_HEIGHT);
    game_states.game_event_state = PLAYING;
    game_states.mouse_state.mouse_b1_pressed = false;
    game_states.mouse_state.mouse_b2_pressed = false;
    game_states.mouse_state.click_sleep = 0.0f;

    program_id = load_shader();
    load_textures();
    init_camera(&camera, program_id);

    world_create(64, 64, &world, &camera);
}

void loop()
{
    bool quit = false;

    SDL_Event e;

    SDL_StartTextInput();

    SDL_ShowCursor(SDL_DISABLE);

    while (!quit)
    {
        game_states.mouse_state.click_sleep += delta_time;
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }

            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
            {
                if (game_states.game_event_state = PAUSE)
                {
                    game_states.game_event_state = PLAYING;
                    SDL_ShowCursor(SDL_DISABLE);
                    SDL_SetWindowGrab(window, SDL_TRUE);
                }
                else
                {
                    game_states.game_event_state = PAUSE;
                    SDL_ShowCursor(SDL_ENABLE);
                    SDL_SetWindowGrab(window, SDL_FALSE);
                }
            }

            if (e.key.keysym.sym == SDLK_a)
            {
                move_camera_left(&camera, delta_time);
            }

            if (e.key.keysym.sym == SDLK_d)
            {
                move_camera_right(&camera, delta_time);
            }

            if (e.key.keysym.sym == SDLK_w)
            {
                move_camera_forward(&camera, delta_time);
            }

            if (e.key.keysym.sym == SDLK_s)
            {
                move_camera_backward(&camera, delta_time);
            }

            if (e.key.keysym.sym == SDLK_SPACE)
            {
                move_camera_vertical(&camera, delta_time);
            }

            if (e.key.keysym.sym == SDLK_LSHIFT)
            {
                move_camera_vertical(&camera, -delta_time);
            }

            if (e.type == SDL_MOUSEBUTTONDOWN)
            {
                if (e.button.button == SDL_BUTTON_LEFT && game_states.mouse_state.click_sleep > 0.8f)
                {
                    game_states.mouse_state.mouse_b1_pressed = true;
                }

                if (e.button.button == SDL_BUTTON_RIGHT && game_states.mouse_state.click_sleep > 0.8f)
                {
                    game_states.mouse_state.mouse_b2_pressed = true;
                }
            }
        }

        if (game_states.game_event_state == PLAYING)
            update();

        render();
        game_states.mouse_state.mouse_b1_pressed = false;
        game_states.mouse_state.mouse_b2_pressed = false;
        SDL_GL_SwapWindow(window);
    }

    clean();
}

void load_textures()
{
    i32 width, height, nrChannels;
    u8 *data = stbi_load("/home/hwilcox/cBlocky/res/atlas.png", &width, &height, &nrChannels, 0);
    if (!data)
    {
        printf("Failed to load texture!\n");
        exit(-1);
    }

    glActiveTexture(GL_TEXTURE0);

    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glEnable(GL_TEXTURE_2D);
    // glEnable(GL_MULTISAMPLE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);
}

void render()
{
    i32 start = SDL_GetTicks();
    i32 startFps = SDL_GetPerformanceCounter();

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    // glClearColor(0.4f, 0.7f, 1.0f, 1);
    glClearColor(0.0f, 0.0f, 0.0f, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(program_id);

    render_world(&world, texture_id);
    render_camera(&camera, program_id);

    int end = SDL_GetTicks();
    float elapsedMS = (end - start) / (f32)SDL_GetPerformanceFrequency() * 1000.0f;
    SDL_Delay(8.66666f - elapsedMS);
    int endFps = SDL_GetPerformanceCounter();
    delta_time = -(f64)((startFps - endFps) / (f32)SDL_GetPerformanceFrequency());
    u32 fps = 1 / ((endFps - startFps) / (f32)SDL_GetPerformanceFrequency());
    char title[128];
    sprintf(title, "CBlocky (%d FPS %f DELTA)", fps, (f32)(delta_time));
    SDL_SetWindowTitle(window, title);
}

void update()
{
    update_world(&world, &game_states);
    SDL_WarpMouseInWindow(window, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
}

void clean()
{
    world_destroy(&world);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
