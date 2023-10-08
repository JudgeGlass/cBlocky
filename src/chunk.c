#include "chunk.h"

void create_mesh(chunk_t *chunk){
    mesh_t mesh;
    f32 *vertices = NULL;
    f32 *textures = NULL;

    glGenVertexArrays(1, &mesh.VAO);
    glBindVertexArray(mesh.VAO);
    glGenBuffers(1, &mesh.VBO);
    glGenBuffers(1, &mesh.TBO);

    for(i32 x = 0; x < CHUNK_WIDTH; x++){
        for(i32 y = 0; y < CHUNK_HEIGHT; y++){
            for(i32 z = 0; z < CHUNK_DEPTH; z++){
                block_t block = chunk->blocks[x + y * CHUNK_WIDTH + z * CHUNK_WIDTH * CHUNK_HEIGHT];

                if(get_type(&block) == AIR){
                    continue;
                }

                u8 id = get_type(&block);
                add_face(x, y, z, chunk->cx, chunk->cz, FRONT, id, &vertices, &textures);
                add_face(x, y, z, chunk->cx, chunk->cz, BACK, id, &vertices, &textures);  
                add_face(x, y, z, chunk->cx, chunk->cz, LEFT, id, &vertices, &textures);
                add_face(x, y, z, chunk->cx, chunk->cz, RIGHT, id, &vertices, &textures);
                add_face(x, y, z, chunk->cx, chunk->cz, TOP, id, &vertices, &textures);
                add_face(x, y, z, chunk->cx, chunk->cz, BOTTOM, id, &vertices, &textures);

            }
        }
    }
   
    i32 size_v = arrlen(vertices);
    i32 size_tex = arrlen(textures);

    glBindVertexArray(mesh.VAO);

    glBindBuffer(GL_ARRAY_BUFFER, mesh.VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(f32) * size_v, vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, mesh.TBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(f32) * size_tex, textures, GL_STATIC_DRAW);

    glBindVertexArray(0);

    mesh.vertex_count = size_v;

    chunk->mesh = mesh;
    arrfree(vertices);
    arrfree(textures);
}

void add_face(u8 x, u8 y, u8 z, i32 cx, i32 cz, face_t face, u8 id, f32 **vertices, f32 **tex_coords){
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
    add_texture_face(id, face, &(*tex_coords));
}

void init_chunk(chunk_t *chunk, i32 cx, i32 cz){
    chunk->cx = cx;
    chunk->cz = cz;
    for(i32 x = 0; x < CHUNK_WIDTH; x++){
        for(i32 y = 0; y < CHUNK_HEIGHT; y++){
            for(i32 z = 0; z < CHUNK_DEPTH; z++){
                block_t block;
                init_block(x, y, z, STONE, 0, &block);

                if(y > 64){
                    //block.id = DIRT;
                    set_type(&block, AIR);
                }else if (y == 64){
                    //block.id = GRASS;
                    set_type(&block, GRASS);
                }else if (y < 64 && y > 60){
                    //block.id = STONE;
                    set_type(&block, DIRT);
                }else if(y < 60){
                    set_type(&block, STONE);
                }

                if(rand() % 3 == 0 && y < 64){
                    //block.id = STONE;
                    set_type(&block, GLASS);
                }

                chunk->blocks[x + y * CHUNK_WIDTH + z * CHUNK_WIDTH * CHUNK_HEIGHT] = block;
            }
        }
    }

    create_mesh(chunk);
}

void draw_chunk(const chunk_t *chunk, u32 texture_id){
    draw_mesh(&chunk->mesh, texture_id);
}

void update_chunk(chunk_t *chunk){

}

void destroy_chunk(chunk_t *chunk){

}