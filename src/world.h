#ifndef __WORLD_H__
#define __WORLD_H__

#include <SDL2/SDL.h>
#include <pthread.h>
#include <time.h>

#include "types.h"
#include "states.h"
#include "block.h"
#include "chunk.h"
#include "camera.h"
#include "ray.h"

#include "open-simplex-noise.h"

static struct osn_context *ctx;

typedef struct
{
    chunk_t *chunks;
    camera_t *camera;
    u32 chunk_amt_width;
    u32 chunk_amt_depth;
} world_t;

typedef struct
{
    u32 start;
    u32 end;
    world_t *world;
} thread_gen_chunk_t;

void world_create(u32 chunk_amt_width, u32 chunk_amt_depth, world_t *world, camera_t *camera);
void world_destroy(world_t *world);
void render_world(world_t *world, u32 texture_id);
void update_world(world_t *world, game_states_t *game_states);

static void *thread_gen_chunk(void *sew);

#endif