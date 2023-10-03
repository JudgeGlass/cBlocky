#include "chunk.h"

void create_mesh(chunk_t *chunk){
    mesh_t mesh;
    f32 *vertices = NULL;

    glGenVertexArrays(1, &mesh.VAO);
    glGenBuffers(1, &mesh.VBO);

    for(i32 x = 0; x < CHUNK_WIDTH; x++){
        for(i32 y = 0; y < CHUNK_HEIGHT; y++){
            for(i32 z = 0; z < CHUNK_DEPTH; z++){
                block_t block = chunk->blocks[x + y * CHUNK_WIDTH + z * CHUNK_WIDTH * CHUNK_HEIGHT];

                if(block.id == AIR){
                    continue;
                }

                add_face(x, y, z, chunk->cx, chunk->cz, FRONT, block.id, &vertices);
                add_face(x, y, z, chunk->cx, chunk->cz, BACK, block.id, &vertices);  
                add_face(x, y, z, chunk->cx, chunk->cz, LEFT, block.id, &vertices);
                add_face(x, y, z, chunk->cx, chunk->cz, RIGHT, block.id, &vertices);
                add_face(x, y, z, chunk->cx, chunk->cz, TOP, block.id, &vertices);
                add_face(x, y, z, chunk->cx, chunk->cz, BOTTOM, block.id, &vertices);

            }
        }
    }

    i32 size = arrlen(vertices);

    glBindVertexArray(mesh.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(f32) * size, vertices, GL_STATIC_DRAW);
    glBindVertexArray(0);

    mesh.vertex_count = size;

    chunk->mesh = mesh;
    arrfree(vertices);
}

void add_face(u8 x, u8 y, u8 z, i32 cx, i32 cz, face_t face, u8 id, f32 **vertices){
    const float *current_face;
    switch (face)
    {
    case FRONT:
        current_face = cube_vertex_front;
        break;
    case BACK:
        current_face = cube_vertex_back;
        break;
    case LEFT:
        current_face = cube_vertex_left;
        break;
    case RIGHT:
        current_face = cube_vertex_right;
        break;
    case TOP:
        current_face = cube_vertex_top;
        break;
    case BOTTOM:
        current_face = cube_vertex_bottom;
        break;
    
    default:
        break;
    }

    for(int i = 0; i < 18; i+=3){
        arrpush(*vertices, current_face[i] + x + cx * CHUNK_WIDTH);
        arrpush(*vertices, current_face[i + 1] + y);
        arrpush(*vertices, current_face[i + 2] + z + cz * CHUNK_DEPTH);
    }
}

void init_chunk(chunk_t *chunk, i32 cx, i32 cz){
    for(i32 x = 0; x < CHUNK_WIDTH; x++){
        for(i32 y = 0; y < CHUNK_HEIGHT; y++){
            for(i32 z = 0; z < CHUNK_DEPTH; z++){
                block_t block;
                block.id = AIR;
                block.x = x;
                block.y = y;
                block.z = z;

                if(y < 64){
                    block.id = DIRT;
                }

                chunk->blocks[x + y * CHUNK_WIDTH + z * CHUNK_WIDTH * CHUNK_HEIGHT] = block;
            }
        }
    }

    create_mesh(chunk);
}

void draw_chunk(const chunk_t *chunk){
    draw_mesh(&chunk->mesh);
}

void update_chunk(chunk_t *chunk){

}

void destroy_chunk(chunk_t *chunk){

}