#include "world.h"

void world_create(u32 chunk_amt_width, u32 chunk_amt_depth, world_t *world, camera_t *camera){
    world->camera = camera;
    world->chunks = (chunk_t*) malloc(sizeof(chunk_t) * chunk_amt_width * chunk_amt_depth);
    world->chunk_amt_width = chunk_amt_width;
    world->chunk_amt_depth = chunk_amt_depth;

    for(u32 w = 0; w < chunk_amt_width; w++){
        for(u32 d = 0; d < chunk_amt_depth; d++){
            init_chunk(&world->chunks[w + chunk_amt_width * d], w, d);
        }
    }

    for(u32 w = 0; w < chunk_amt_width; w++){
        for(u32 d = 0; d < chunk_amt_depth; d++){
            create_mesh(&world->chunks[w + chunk_amt_width * d], world->chunks);
        }
    }

    
}

void world_destroy(world_t *world){
    free(world->chunks);
}

void render_world(world_t *world, u32 texture_id){
    for(u32 i = 0; i < world->chunk_amt_width * world->chunk_amt_depth; i++){
        f32 cam_x = world->camera->position[0];
        f32 cam_z = world->camera->position[2];
        vec2 player_2d_pos = {cam_x, cam_z};

        chunk_t *chunk = &world->chunks[i];
        vec2 chunk_2d_pos = {chunk->cx * CHUNK_WIDTH, chunk->cz * CHUNK_DEPTH};

        if(glm_vec2_distance(player_2d_pos, chunk_2d_pos) < 128.0f){
            draw_chunk(chunk, texture_id);
        }
        
    }
}

void update_world(world_t *world, game_states_t *game_states){
    update_camera(world->camera);
    for(u32 i = 0; i < world->chunk_amt_width * world->chunk_amt_depth; i++){
        update_chunk(&world->chunks[i]);
    }


    f32 yaw = world->camera->yaw;
    f32 pitch = world->camera->pitch;
    vec3 cam_pos = {world->camera->position[0], world->camera->position[1] + 0.5f, world->camera->position[2]};
    ray_t ray;
    init_ray(&ray, cam_pos, yaw, pitch);

    for(; ray_length(&ray) < 6; ray_step(&ray, 0.05f)){
        f32 x = ray_end(&ray)[0];
        f32 y = ray_end(&ray)[1];
        f32 z = ray_end(&ray)[2];

        i32 cx = (i32) x / 16;
        i32 cz = (i32) z / 16;

        if(cx < 0 || cz < 0 || cx > 15 || cz > 15) break;

        int xx = (int) x % 16;
        int yy = (int) y;
        int zz = (int) z % 16;

        block_t *block = get_block(get_chunk(world->chunks, world->chunk_amt_width, world->chunk_amt_depth, cx, cz), (u8) x % 16, (u8) y, (u8) z % 16);
        
        if(get_type(block) != AIR){
            if(game_states->mouse_state.mouse_b1_pressed){
                set_block(get_chunk(world->chunks, world->chunk_amt_width, world->chunk_amt_depth, cx, cz), (u8) x % 16, (u8) y, (u8) z % 16, AIR);               
                create_mesh(get_chunk(world->chunks, world->chunk_amt_width, world->chunk_amt_depth, cx, cz), world->chunks);
                game_states->mouse_state.click_sleep = 0.0f;
            }

            if(game_states->mouse_state.mouse_b2_pressed){
                set_block(get_chunk(world->chunks, world->chunk_amt_width, world->chunk_amt_depth, cx, cz), (u8) x % 16, (u8) y + 1, (u8) z % 16, GRASS);               
                create_mesh(get_chunk(world->chunks, world->chunk_amt_width, world->chunk_amt_depth, cx, cz), world->chunks);
                game_states->mouse_state.click_sleep = 0.0f;
            }
        }
    }

}