#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include <GL/glew.h>
#include <cglm/cglm.h>

#ifndef STB_DS_IMPLEMENTATION
#include <stb_ds.h>
#endif

#include "types.h"
#include "block.h"

typedef struct
{
    vec2 uv_right_face;
    vec2 uv_left_face;
    vec2 uv_top_face;
    vec2 uv_bottom_face;
    vec2 uv_front_face;
    vec2 uv_back_face;
} texture_t;

typedef struct
{
    u8 block_id;
    const u8 texture_face_index[6];
} block_texture_t;

// 0 Top, 1 Bottom, 2 Front, 3 Back, 4 Left, 5 Right
static block_texture_t block_textures[16 * 16] = {
    {DIRT, {3, 3, 3, 3, 3, 3}},
    {GRASS, {1, 3, 2, 2, 2, 2}},
    {STONE, {0, 0, 0, 0, 0, 0}},
    {OAK_LOG, {19, 19, 20, 20, 20, 20}},
    {OAK_LEAVES, {25, 25, 25, 25, 25, 25}},
    {GLASS, {29, 29, 29, 29, 29, 29}}};

static void get_texture_uvs(const u8 block_id, f32 *uvarr);
static void get_texture_uvs_face(const u8 face, f32 *uvarr);

void add_texture_face(const u8 block_id, face_t face, f32 **texture_coords);

#endif