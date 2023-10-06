#ifndef __WORLD_H__
#define __WORLD_H__

#include "types.h"
#include "block.h"
#include "chunk.h"
#include "camera.h"

typedef struct {
    chunk_t *chunks;
    camera_t *camera;
    u32 chunk_amt_width;
    u32 chunk_amt_depth;
} world_t;

world_t *world_create(u32 chunk_amt_width, u32 chunk_amt_depth);
void world_destroy(world_t *world);
void render_world(world_t *world);
void update_world(world_t *world);

#endif