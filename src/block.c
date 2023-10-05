#include "block.h"

void init_block(u8 x, u8 y, u8 z, u8 id, u8 light_level, block_t *block){
    block->data |= (u32)((x << 4) | light_level) << 24;
    block->data |= (u32)((z << 4) | 0) << 16;
    block->data |= (u32)y << 8;
    block->data |= (u32)id;
}

 void set_type(block_t *block, u8 type){
    //this->type = type;
    block->data &= 0xFFFFFF00;
    block->data |= (u32)type;
}

u8 get_x(block_t *block){
    //return x;
    return (block->data >> 28) & 0xF;
}

u8 get_y(block_t *block) {
    //return y;
    return (block->data >> 8) & 0xFF;
}

u8 get_z(block_t *block) {
    //return z;
    return (block->data >> 20) & 0xF;
}

u8 get_light(block_t *block) {
    //return light;
    return (block->data >> 24) & 0xF;
}

u8 get_is_sky(block_t *block) {
    //return is_sky;
    return (block->data >> 16) & 0xF;
}

u8 get_type(block_t *block) {
//            return type;
    return (block->data) & 0xFF;
}