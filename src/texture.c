#include "texture.h"

void add_texture_face(const u8 block_id, face_t face, f32 **texture_coords){
    if(block_id == AIR) return;

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
        case GLASS:
            arrpush(*texture_coords, texture_uv_glass[i]);
            break;
        default:
            return;
        }
    }
}