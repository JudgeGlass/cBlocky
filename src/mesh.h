#ifndef __MESH_H__
#define __MESH_H__

#include <GL/glew.h>

#include "types.h"

static const f32 cube_vertex_front[] = { //CCW
    0.5f, 0.5f, 0.5f,
    0.5f, -0.5f, 0.5f,
    0.5f, -0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    0.5f, 0.5f, -0.5f,
    0.5f, 0.5f, 0.5f,

    -0.5f,0.5f,-0.5f, // Left
    -0.5f,-0.5f,-0.5f,
    -0.5f,-0.5f,0.5f,
    -0.5f,-0.5f,0.5f,
    -0.5f,0.5f,0.5f,
    -0.5f,0.5f,-0.5f,

    0.5f,0.5f,-0.5f,
    -0.5f,0.5f,-0.5f,
    -0.5f,0.5f,0.5f,
    -0.5f,0.5f,0.5f,
    0.5f,0.5f,0.5f,
    0.5f,0.5f,-0.5f,

    -0.5f, -0.5f, 0.5f,
    -0.5f, -0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    0.5f, -0.5f, 0.5f,
    -0.5f, -0.5f, 0.5f,

    -0.5f,0.5f,0.5f,
    -0.5f,-0.5f,0.5f,
    0.5f,-0.5f,0.5f,
    0.5f,-0.5f,0.5f,
    0.5f,0.5f,0.5f,
    -0.5f,0.5f,0.5f,

    0.5f, 0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, 0.5f, -0.5f,
    0.5f, 0.5f, -0.5f
};

typedef struct {
    u32 VAO;
    u32 VBO;
    u32 TBO;
    size_t vertex_count;
} mesh_t;

void draw_mesh(const mesh_t *mesh);

#endif