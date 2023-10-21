#ifndef __CHUNK_H__
#define __CHUNK_H__

#define CHUNK_WIDTH 16
#define CHUNK_HEIGHT 256
#define CHUNK_DEPTH 16

#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <GL/glew.h>

#include "types.h"
#include "block.h"
#include "mesh.h"
#include "texture.h"
#include "open-simplex-noise.h"

typedef struct {
    i32 cx;
    i32 cz;
    block_t blocks[CHUNK_WIDTH * CHUNK_HEIGHT * CHUNK_DEPTH];
    mesh_t mesh;
} chunk_t;

static void add_face(u8 x, u8 y, u8 z, chunk_t *chunk, face_t face, u8 id, f32 **vertices, f32 **tex_coords, chunk_t *world_chunks);
static u8 is_face_visible(i32 x, i32 y, i32 z, chunk_t *chunk, face_t face, u8 id, chunk_t *world_chunks);
static void create_tree(chunk_t *chunk, i32 x, i32 y, i32 z);

void init_chunk(chunk_t *chunk, i32 cx, i32 cz);
void create_mesh(chunk_t *chunk, chunk_t *world_chunks);
void draw_chunk(const chunk_t *chunk, u32 texture_id);
void update_chunk(chunk_t *chunk);
void destroy_chunk(chunk_t *chunk);
void set_block(chunk_t *chunk, u8 x, u8 y, u8 z, u8 type);

chunk_t *get_chunk(chunk_t *chunks, u32 chunk_amt_width, u32 chunk_amt_depth, i32 cx, i32 cz);
block_t *get_block(chunk_t *chunk, u8 x, u8 y, u8 z);

#endif