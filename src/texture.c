#include "texture.h"

void get_texture_uvs(const u8 block_id, f32 *uvarr)
{
    const u8 *texture_info;
    for (int i = 0; i < 16 * 16; i++)
    {
        if (block_textures[i].block_id == block_id)
        {
            texture_info = block_textures[i].texture_face_index;
            break;
        }
    }

    u8 top = texture_info[0];
    u8 bottom = texture_info[1];
    u8 front = texture_info[2];
    u8 back = texture_info[3];
    u8 left = texture_info[4];
    u8 right = texture_info[5];

    u8 corrected_faces[6] = {right, left, top, bottom, front, back}; // Fix ordering later
    u8 offset = 0;
    for (int i = 0; i < 6; i++, offset += 12)
    {
        f32 face_uvs[12];
        u8 face = corrected_faces[i];
        get_texture_uvs_face(face, face_uvs);
        for (int j = 0; j < 12; j++)
        {
            uvarr[j + offset] = face_uvs[j];
        }
    }
}

void get_texture_uvs_face(const u8 face, f32 *uvarr)
{
    f32 tx = (int)(face % 16);
    f32 ty = (int)(face / 16);

    f32 q1x = tx / 16;
    f32 q1y = ty / 16;
    f32 q2x = (tx + 1) / 16;
    f32 q2y = q1y;
    f32 q3x = q2x;
    f32 q3y = (ty + 1) / 16;
    f32 q4x = q1x;
    f32 q4y = q3y;

    // return size 12 f32 array
    uvarr[0] = q1x;
    uvarr[1] = q1y;
    uvarr[2] = q4x;
    uvarr[3] = q4y;
    uvarr[4] = q3x;
    uvarr[5] = q3y;
    uvarr[6] = q3x;
    uvarr[7] = q3y;
    uvarr[8] = q2x;
    uvarr[9] = q2y;
    uvarr[10] = q1x;
    uvarr[11] = q1y;
}

void add_texture_face(const u8 block_id, face_t face, f32 **texture_coords)
{
    if (block_id == AIR)
        return;

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

    f32 uvsarr[72];
    get_texture_uvs(block_id, uvsarr);
    for (int i = offset; i < offset + 12; i++)
    {
        arrpush(*texture_coords, uvsarr[i]);
    }
}