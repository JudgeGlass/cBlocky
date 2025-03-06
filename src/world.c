#include "world.h"

void world_create(u32 chunk_amt_width, u32 chunk_amt_depth, world_t *world, camera_t *camera)
{
    world->camera = camera;
    world->chunks = (chunk_t *)malloc(sizeof(chunk_t) * chunk_amt_width * chunk_amt_depth);
    world->chunk_amt_width = chunk_amt_width;
    world->chunk_amt_depth = chunk_amt_depth;
    open_simplex_noise(77374, &ctx);

    // for (u32 w = 0; w < chunk_amt_width; w++)
    // {
    //     for (u32 d = 0; d < chunk_amt_depth; d++)
    //     {
    //         init_chunk(&world->chunks[w + chunk_amt_width * d], w, d);
    //     }
    // }

    int p_cores = 16;
    pthread_t thread_ids[p_cores];
    thread_gen_chunk_t info[p_cores];

    int array_size = chunk_amt_depth * chunk_amt_width;
    int r = array_size % p_cores;
    int thread_chunk_size = (array_size - r) / p_cores;

    for (int i = 0; i < (thread_chunk_size * p_cores); i += thread_chunk_size)
    {
        int core = i / thread_chunk_size;
        int my_first_i = i;
        int my_last_i = i + thread_chunk_size - 1;

        // If the sum cannot be evenly divided, give last core more work.
        if (core == p_cores - 1)
        {
            my_last_i += r;
        }

        // printf("core %d: my_first_i = %d, my_last_i = %d\n", core, my_first_i, my_last_i);
        info[core].start = my_first_i;
        info[core].end = my_last_i;
        info[core].world = world;
    }

    time_t start, end;

    time(&start);

    for (int i = 0; i < p_cores; i++)
    {
        if (pthread_create(&thread_ids[i], NULL, thread_gen_chunk, (void *)&info[i]) != 0)
        {
            printf("FAILED TO CREATE THREAD!\n");
            exit(-1);
        }
    }

    int threads_left = p_cores;
    for (int i = 0; i < p_cores; i++)
    {
        printf("Threads remaining: %d\n", threads_left);
        pthread_join(thread_ids[i], NULL);
        threads_left--;
    }

    time(&end);

    printf("Chunk gen done! %.2f second(s)\n", difftime(end, start));

    // for (u32 w = 0; w < chunk_amt_width; w++)
    // {
    //     for (u32 d = 0; d < chunk_amt_depth; d++)
    //     {
    //         create_mesh(&world->chunks[w + chunk_amt_width * d], world->chunks);
    //     }
    // }

    printf("Chunk mesh done!\n");
}

void *thread_gen_chunk(void *sew)
{
    thread_gen_chunk_t *info = (thread_gen_chunk_t *)sew;
    // printf("Start: %d  End: %d\n", info->start, info->end);
    for (int i = info->start; i < info->end; i++)
    {
        int w = i % 32;
        int d = i / 32;
        // printf("I: %d E: %d\n", i, info->end);
        init_chunk(&info->world->chunks[w + 32 * d], w, d, ctx);
    }

    for (int i = info->start; i < info->end; i++)
    {
        int w = i % 32;
        int d = i / 32;
        // printf("I: %d E: %d\n", i, info->end);
        create_mesh(&info->world->chunks[w + 32 * d], info->world->chunks);
    }

    return NULL;
}

void world_destroy(world_t *world)
{
    free(world->chunks);
}

void render_world(world_t *world, u32 texture_id)
{
    for (u32 i = 0; i < world->chunk_amt_width * world->chunk_amt_depth; i++)
    {
        f32 cam_x = world->camera->position[0];
        f32 cam_z = world->camera->position[2];
        vec2 player_2d_pos = {cam_x, cam_z};

        chunk_t *chunk = &world->chunks[i];
        vec2 chunk_2d_pos = {chunk->cx * CHUNK_WIDTH, chunk->cz * CHUNK_DEPTH};

        if (glm_vec2_distance(player_2d_pos, chunk_2d_pos) < 128.0f)
        {
            draw_chunk(chunk, texture_id);
        }
    }
}

void update_world(world_t *world, game_states_t *game_states)
{
    update_camera(world->camera);
    for (u32 i = 0; i < world->chunk_amt_width * world->chunk_amt_depth; i++)
    {
        update_chunk(&world->chunks[i]);
    }

    f32 yaw = world->camera->yaw;
    f32 pitch = world->camera->pitch;
    vec3 cam_pos = {world->camera->position[0], world->camera->position[1] + 0.5f, world->camera->position[2]};
    ray_t ray;
    init_ray(&ray, cam_pos, yaw, pitch);

    for (; ray_length(&ray) < 6; ray_step(&ray, 0.05f))
    {
        f32 x = ray_end(&ray)[0];
        f32 y = ray_end(&ray)[1];
        f32 z = ray_end(&ray)[2];

        i32 cx = (i32)x / 16;
        i32 cz = (i32)z / 16;

        if (cx < 0 || cz < 0 || cx > 15 || cz > 15)
            break;

        int xx = (int)x % 16;
        int yy = (int)y;
        int zz = (int)z % 16;

        block_t *block = get_block(get_chunk(world->chunks, world->chunk_amt_width, world->chunk_amt_depth, cx, cz), (u8)x % 16, (u8)y, (u8)z % 16);

        if (get_type(block) != AIR)
        {
            if (game_states->mouse_state.mouse_b1_pressed)
            {
                set_block(get_chunk(world->chunks, world->chunk_amt_width, world->chunk_amt_depth, cx, cz), (u8)x % 16, (u8)y, (u8)z % 16, AIR);
                create_mesh(get_chunk(world->chunks, world->chunk_amt_width, world->chunk_amt_depth, cx, cz), world->chunks);
                game_states->mouse_state.click_sleep = 0.0f;
            }

            if (game_states->mouse_state.mouse_b2_pressed)
            {
                set_block(get_chunk(world->chunks, world->chunk_amt_width, world->chunk_amt_depth, cx, cz), (u8)x % 16, (u8)y + 1, (u8)z % 16, GRASS);
                create_mesh(get_chunk(world->chunks, world->chunk_amt_width, world->chunk_amt_depth, cx, cz), world->chunks);
                game_states->mouse_state.click_sleep = 0.0f;
            }
        }
    }
}