#ifndef __BLOCK_H__
#define __BLOCK_H__

#include "types.h"

#define AIR 0
#define DIRT 1
#define GRASS 2
#define STONE 3
#define OAK_LOG 4
#define OAK_LEAVES 5
#define GLASS 15

typedef struct {
    u32 data;
} block_t;

typedef enum {
    FRONT,
    BACK,
    LEFT,
    RIGHT,
    TOP,
    BOTTOM
} face_t;

void init_block(u8 x, u8 y, u8 z, u8 id, u8 light_level, block_t *block);

void set_type(block_t *block, u8 type);

u8 get_x(block_t *block);

u8 get_y(block_t *block);

u8 get_z(block_t *block);

u8 get_light(block_t *block);

u8 get_is_sky(block_t *block);

u8 get_type(block_t *block);


#endif