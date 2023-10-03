#ifndef __BLOCK_H__
#define __BLOCK_H__

#include "types.h"

#define AIR 0
#define DIRT 1
#define GRASS 2
#define STONE 3

typedef struct {
    u8 id;
    u8 x;
    u8 y;
    u8 z;
} block_t;

typedef enum {
    FRONT,
    BACK,
    LEFT,
    RIGHT,
    TOP,
    BOTTOM
} face_t;


#endif