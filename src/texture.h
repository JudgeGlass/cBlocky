#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include <GL/glew.h>
#include <stb_ds.h>

#include "types.h"
#include "block.h"


static const f32 texture_uv_grass[] = {
    0.125f, 0.0f,   // RIGHT
    0.125f, 0.0625f,
    0.1875f, 0.0625f,
    0.1875f, 0.0625f,
    0.1875f, 0.f,
    0.125f, 0.f,

    0.125f, 0.0f, // LEFT
    0.125f, 0.0625f,
    0.1875f, 0.0625f,
    0.1875f, 0.0625f,
    0.1875f, 0.f,
    0.125f, 0.f,

    0.0625f, 0.0f, // TOP
    0.0625f, 0.0625f,
    0.125f, 0.0625,
    0.125f, 0.0625f,
    0.125f, 0.0f,
    0.0625f, 0.0f,

    3.0f/16.0f, 0.0f, // BOTTOM
    3.0f/16.0f, 1.0f/16.0f,
    4.0f/16.0f, 1.0f/16.0f,
    4.0f/16.0f, 1.0f/16.0f,
    4.0f/16.0f, 0.0f,
    3.0f/16.0f, 0.0f,


    0.125f, 0.0f, // FRONT
    0.125f, 0.0625f,
    0.1875f, 0.0625f,
    0.1875f, 0.0625f,
    0.1875f, 0.f,
    0.125f, 0.f,

    0.125f, 0.0f,   // BACK
    0.125f, 0.0625f,
    0.1875f, 0.0625f,
    0.1875f, 0.0625f,
    0.1875f, 0.f,
    0.125f, 0.f
};

static const f32 texture_uv_stone[] = {
    0.0f, 0.0f,
    0.0f, 1.0f/16.0f,
    1.0f/16.0f, 1.0f/16.0f,
    1.0f/16.0f, 1.0f/16.0f,
    1.0f/16.0f, 0.0f,
    0.0f, 0.0f,
    0.0f, 0.0f,
    0.0f, 1.0f/16.0f,
    1.0f/16.0f, 1.0f/16.0f,
    1.0f/16.0f, 1.0f/16.0f,
    1.0f/16.0f, 0.0f,
    0.0f, 0.0f,
    0.0f, 0.0f,
    0.0f, 1.0f/16.0f,
    1.0f/16.0f, 1.0f/16.0f,
    1.0f/16.0f, 1.0f/16.0f,
    1.0f/16.0f, 0.0f,
    0.0f, 0.0f,
    0.0f, 0.0f,
    0.0f, 1.0f/16.0f,
    1.0f/16.0f, 1.0f/16.0f,
    1.0f/16.0f, 1.0f/16.0f,
    1.0f/16.0f, 0.0f,
    0.0f, 0.0f,
    0.0f, 0.0f,
    0.0f, 1.0f/16.0f,
    1.0f/16.0f, 1.0f/16.0f,
    1.0f/16.0f, 1.0f/16.0f,
    1.0f/16.0f, 0.0f,
    0.0f, 0.0f,
    0.0f, 0.0f,
    0.0f, 1.0f/16.0f,
    1.0f/16.0f, 1.0f/16.0f,
    1.0f/16.0f, 1.0f/16.0f,
    1.0f/16.0f, 0.0f,
    0.0f, 0.0f
};

static const f32 texture_uv_glass[] = {
    13.0f/16.0f, 1.0f/16.0f,
    13.0f/16.0f, 2.0f/16.0f,
    14.0f/16.0f, 2.0f/16.0f,
    14.0f/16.0f, 2.0f/16.0f,
    14.0f/16.0f, 1.0f/16.0f,
    13.0f/16.0f, 1.0f/16.0f,
    13.0f/16.0f, 1.0f/16.0f,
    13.0f/16.0f, 2.0f/16.0f,
    14.0f/16.0f, 2.0f/16.0f,
    14.0f/16.0f, 2.0f/16.0f,
    14.0f/16.0f, 1.0f/16.0f,
    13.0f/16.0f, 1.0f/16.0f,
    13.0f/16.0f, 1.0f/16.0f,
    13.0f/16.0f, 2.0f/16.0f,
    14.0f/16.0f, 2.0f/16.0f,
    14.0f/16.0f, 2.0f/16.0f,
    14.0f/16.0f, 1.0f/16.0f,
    13.0f/16.0f, 1.0f/16.0f,
    13.0f/16.0f, 1.0f/16.0f,
    13.0f/16.0f, 2.0f/16.0f,
    14.0f/16.0f, 2.0f/16.0f,
    14.0f/16.0f, 2.0f/16.0f,
    14.0f/16.0f, 1.0f/16.0f,
    13.0f/16.0f, 1.0f/16.0f,
    13.0f/16.0f, 1.0f/16.0f,
    13.0f/16.0f, 2.0f/16.0f,
    14.0f/16.0f, 2.0f/16.0f,
    14.0f/16.0f, 2.0f/16.0f,
    14.0f/16.0f, 1.0f/16.0f,
    13.0f/16.0f, 1.0f/16.0f,
    13.0f/16.0f, 1.0f/16.0f,
    13.0f/16.0f, 2.0f/16.0f,
    14.0f/16.0f, 2.0f/16.0f,
    14.0f/16.0f, 2.0f/16.0f,
    14.0f/16.0f, 1.0f/16.0f,
    13.0f/16.0f, 1.0f/16.0f,
};

static const f32 texture_uv_dirt[] = {
    3.0f/16.0f, 0.0f,
    3.0f/16.0f, 1.0f/16.0f,
    4.0f/16.0f, 1.0f/16.0f,
    4.0f/16.0f, 1.0f/16.0f,
    4.0f/16.0f, 0.0f,
    3.0f/16.0f, 0.0f,
    3.0f/16.0f, 0.0f,
    3.0f/16.0f, 1.0f/16.0f,
    4.0f/16.0f, 1.0f/16.0f,
    4.0f/16.0f, 1.0f/16.0f,
    4.0f/16.0f, 0.0f,
    3.0f/16.0f, 0.0f,
    3.0f/16.0f, 0.0f,
    3.0f/16.0f, 1.0f/16.0f,
    4.0f/16.0f, 1.0f/16.0f,
    4.0f/16.0f, 1.0f/16.0f,
    4.0f/16.0f, 0.0f,
    3.0f/16.0f, 0.0f,
    3.0f/16.0f, 0.0f,
    3.0f/16.0f, 1.0f/16.0f,
    4.0f/16.0f, 1.0f/16.0f,
    4.0f/16.0f, 1.0f/16.0f,
    4.0f/16.0f, 0.0f,
    3.0f/16.0f, 0.0f,
    3.0f/16.0f, 0.0f,
    3.0f/16.0f, 1.0f/16.0f,
    4.0f/16.0f, 1.0f/16.0f,
    4.0f/16.0f, 1.0f/16.0f,
    4.0f/16.0f, 0.0f,
    3.0f/16.0f, 0.0f,
    3.0f/16.0f, 0.0f,
    3.0f/16.0f, 1.0f/16.0f,
    4.0f/16.0f, 1.0f/16.0f,
    4.0f/16.0f, 1.0f/16.0f,
    4.0f/16.0f, 0.0f,
    3.0f/16.0f, 0.0f
};

void add_texture_face(const u8 block_id, face_t face, f32 **texture_coords){
    if(block_id == 0) return;

    int offset = 0;
    switch (face)
    {
    case FRONT:
        offset = 4 * 12;
        break;
    case BACK:
        offset = 5 * 12;
        break;
    case LEFT:
        offset = 12;
        break;
    case RIGHT:
        offset = 0;
        break;
    case TOP:
        offset = 2 * 12;
        break;
    case BOTTOM:
        offset = 3 * 12;
        break;
    default:
        offset = 0;
        break;
    }

    for(int i = offset; i < offset + 12; i++){
        switch (block_id)
        {
        case AIR:
            return;
        case GRASS:
            arrpush(*texture_coords, texture_uv_grass[i]);
            break;
        case STONE:
            arrpush(*texture_coords, texture_uv_stone[i]);
            break;
        case DIRT:
            arrpush(*texture_coords, texture_uv_dirt[i]);
            break;
        // case GLASS:
        //     texture_coords.push_back(texture_uv_glass[i]);
        //     break;
        default:
            return;
        }
    }
}


#endif