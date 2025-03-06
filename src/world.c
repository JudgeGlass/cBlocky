#include "world.h"

void world_create(u32 chunk_amt_width, u32 chunk_amt_depth, world_t *world, camera_t *camera)
{
    world->camera = camera;
    world->chunks = (chunk_t *)malloc(sizeof(chunk_t) * chunk_amt_width * chunk_amt_depth);
    world->chunk_amt_width = chunk_amt_width;
    world->chunk_amt_depth = chunk_amt_depth;
    open_simplex_noise(77374, &ctx);

    int p_cores = 8;
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
        printf("Threads remaining (chunk gen): %d\n", threads_left);
        pthread_join(thread_ids[i], NULL);
        threads_left--;
    }

    for (int i = 0; i < p_cores; i++)
    {
        if (pthread_create(&thread_ids[i], NULL, thread_gen_chunk_mesh, (void *)&info[i]) != 0)
        {
            printf("FAILED TO CREATE THREAD!\n");
            exit(-1);
        }
    }

    threads_left = p_cores;
    for (int i = 0; i < p_cores; i++)
    {
        printf("Threads remaining (mesh gen): %d\n", threads_left);
        pthread_join(thread_ids[i], NULL);
        for (int j = 0; j < (info[i].end - info[i].start); j++)
        {
            mesh_t mesh = info[i].chunk_mesh[j].mesh;
            i32 size_v = info[i].chunk_mesh[j].size_v;
            i32 size_tex = info[i].chunk_mesh[j].size_tex;
            f32 *vertices = info[i].chunk_mesh[j].vertices;
            f32 *textures = info[i].chunk_mesh[j].textures;
            i32 s = arrlen(vertices);
            glGenVertexArrays(1, &mesh.VAO);
            glBindVertexArray(mesh.VAO);
            glGenBuffers(1, &mesh.VBO);
            glGenBuffers(1, &mesh.TBO);
            glBindVertexArray(mesh.VAO);

            glBindBuffer(GL_ARRAY_BUFFER, mesh.VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(f32) * size_v, vertices, GL_STATIC_DRAW);

            glBindBuffer(GL_ARRAY_BUFFER, mesh.TBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(f32) * size_tex, textures, GL_STATIC_DRAW);

            glBindVertexArray(0);
            info[i].chunk_mesh[j].chunk->mesh = mesh;
            arrfree(vertices);
            arrfree(textures);
        }
        threads_left--;
        free(info[i].chunk_mesh);
    }

    time(&end);

    printf("Chunk gen done! %.2f second(s)\n", difftime(end, start));
}

void *thread_gen_chunk(void *sew)
{
    thread_gen_chunk_t *info = (thread_gen_chunk_t *)sew;
    for (int i = info->start; i < info->end; i++)
    {
        int w = i % 64;
        int d = i / 64;
        init_chunk(&info->world->chunks[w + 64 * d], w, d, ctx);
    }
    return NULL;
}

void *thread_gen_chunk_mesh(void *sew)
{
    thread_gen_chunk_t *info = (thread_gen_chunk_t *)sew;
    chunk_mesh_t *chunk_meshes = (chunk_mesh_t *)malloc(sizeof(chunk_mesh_t) * (info->end - info->start));
    for (int i = info->start; i < info->end; i++)
    {
        int w = i % 64;
        int d = i / 64;
        chunk_meshes[i - info->start] = create_mesh(&info->world->chunks[w + 64 * d], info->world->chunks);
        info->world->chunks[w + 64 * d].mesh = chunk_meshes[i - info->start].mesh;
    }

    info->chunk_mesh = chunk_meshes;
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