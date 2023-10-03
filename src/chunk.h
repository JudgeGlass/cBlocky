#ifndef __CHUNK_H__
#define __CHUNK_H__

#define CHUNK_WIDTH 16
#define CHUNK_HEIGHT 256
#define CHUNK_DEPTH 16

#include <GL/glew.h>
#include <stb_ds.h>

#include "types.h"
#include "block.h"
#include "mesh.h"

typedef struct {
    i32 cx;
    i32 cz;
    block_t blocks[CHUNK_WIDTH * CHUNK_HEIGHT * CHUNK_DEPTH];
    mesh_t mesh;
} chunk_t;

static void create_mesh(chunk_t *chunk);
static void add_face(u8 x, u8 y, u8 z, i32 cx, i32 cz, face_t face, u8 id, f32 **vertices);

void init_chunk(chunk_t *chunk, i32 cx, i32 cz);
void draw_chunk(const chunk_t *chunk);
void update_chunk(chunk_t *chunk);
void destroy_chunk(chunk_t *chunk);

#endif