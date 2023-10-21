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

void update_world(world_t *world){
    update_camera(world->camera);
    for(u32 i = 0; i < world->chunk_amt_width * world->chunk_amt_depth; i++){
        update_chunk(&world->chunks[i]);
    }
}