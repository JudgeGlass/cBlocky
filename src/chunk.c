#include "chunk.h"

void create_mesh(chunk_t *chunk, chunk_t *world_chunks){
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
                add_face(x, y, z, chunk, FRONT, id, &vertices, &textures, world_chunks);
                add_face(x, y, z, chunk, BACK, id, &vertices, &textures, world_chunks);  
                add_face(x, y, z, chunk, LEFT, id, &vertices, &textures, world_chunks);
                add_face(x, y, z, chunk, RIGHT, id, &vertices, &textures, world_chunks);
                add_face(x, y, z, chunk, TOP, id, &vertices, &textures, world_chunks);
                add_face(x, y, z, chunk, BOTTOM, id, &vertices, &textures, world_chunks);
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

u8 is_face_visible(i32 x, i32 y, i32 z, chunk_t *chunk, face_t face, u8 id, chunk_t *world_chunks){
    i32 cx = chunk->cx;
    i32 cz = chunk->cz;
    
    if(y < 0 || y > CHUNK_HEIGHT - 1){
        return 1;
    }

    block_t *block = NULL;
    if(x < 0){
        if(cx - 1 >= 0){
            block = get_block(get_chunk(world_chunks, 6, 6, cx - 1, cz), 15, y, z);
        }else{
            return 1;
        }
    }else if(x > CHUNK_WIDTH){
        if(cx + 1 < CHUNK_WIDTH){
            block = get_block(get_chunk(world_chunks, 6, 6, cx + 1, cz), 0, y, z);
        }else{
            return 1;
        }
    }else if(z < 0){
        if(cz - 1 >= 0){
            block = get_block(get_chunk(world_chunks, 6, 6, cx, cz - 1), x, y, 15);
        }else{
            return 1;
        }
    }else if(z > CHUNK_DEPTH){
        if(cz + 1 < CHUNK_DEPTH){
            block = get_block(get_chunk(world_chunks, 6, 6, cx, cz + 1), x, y, 0);
        }else{
            return 1;
        }
    }else{
        block = get_block(chunk, x, y, z);
    }

    if(block == NULL) return 1;

    if(get_type(block) == AIR && id == GLASS){
        return 0;
    }

    switch (get_type(block))
    {
    case AIR:
    case GLASS:
        return 1;
    
    default:
        return 0;
    }

    return 1;
}

void add_face(u8 x, u8 y, u8 z, chunk_t *chunk, face_t face, u8 id, f32 **vertices, f32 **tex_coords, chunk_t *world_chunks){
    i32 cx = chunk->cx;
    i32 cz = chunk->cz;
    i32 xx = x, yy = y, zz = z;

    const float *current_face;
    switch (face)
    {
    case FRONT:
        zz += 1;
        current_face = cube_vertex_front;
        break;
    case BACK:
        zz -= 1;
        current_face = cube_vertex_back;
        break;
    case LEFT:
        xx -= 1;
        current_face = cube_vertex_left;
        break;
    case RIGHT:
        xx += 1;
        current_face = cube_vertex_right;
        break;
    case TOP:
        yy += 1;
        current_face = cube_vertex_top;
        break;
    case BOTTOM:
        yy -= 1;
        current_face = cube_vertex_bottom;
        break;
    
    default:
        break;
    }

    if(is_face_visible(xx, yy, zz, chunk, face, id, world_chunks) && id != AIR){
        for(int i = 0; i < 18; i+=3){
            arrpush(*vertices, current_face[i] + x + cx * CHUNK_WIDTH);
            arrpush(*vertices, current_face[i + 1] + y);
            arrpush(*vertices, current_face[i + 2] + z + cz * CHUNK_DEPTH);
        }
        add_texture_face(id, face, &(*tex_coords));
    }
}

block_t *get_block(chunk_t *chunk, u8 x, u8 y, u8 z){
    return &chunk->blocks[x + y * CHUNK_WIDTH + z * CHUNK_WIDTH * CHUNK_HEIGHT];
}

void init_chunk(chunk_t *chunk, i32 cx, i32 cz){
    chunk->cx = cx;
    chunk->cz = cz;

    struct osn_context *ctx;
    open_simplex_noise(77374, &ctx);

    for(i32 x = 0; x < CHUNK_WIDTH; x++){
        for(i32 y = 0; y < CHUNK_HEIGHT; y++){
            for(i32 z = 0; z < CHUNK_DEPTH; z++){
                
                f32 xx = (x+cx*CHUNK_WIDTH + ((f32)rand() / RAND_MAX) / 80);
                f32 yy = (f32)(z + cz * CHUNK_DEPTH) + ((f32)(rand() / RAND_MAX) / 80);
                f32 n = fabs(open_simplex_noise2(ctx, xx, yy)) * 12;

                u32 l_start = (u32) n + 120;

                block_t block;
                init_block(x, y, z, STONE, 0, &block);

                if(y < 20 && y > 15){
                    set_type(&block, AIR);
                }

                if(y < l_start){
                    if(y == l_start - 1)
                        set_type(&block, GRASS);
                    else if(y < l_start - 1 && y > l_start - 5)
                        set_type(&block, DIRT);
                    else
                        set_type(&block, STONE);
                }else{
                    set_type(&block, AIR);
                }

                chunk->blocks[x + y * CHUNK_WIDTH + z * CHUNK_WIDTH * CHUNK_HEIGHT] = block;
            }
        }
    }

    
}

chunk_t *get_chunk(chunk_t *chunks, u32 chunk_amt_width, u32 chunk_amt_depth, i32 cx, i32 cz){
    if(cx < 0 || cz < 0 || cx >= chunk_amt_width || cz >= chunk_amt_depth){
        return NULL;
    }

    return &chunks[cx + cz * chunk_amt_width];
}

void draw_chunk(const chunk_t *chunk, u32 texture_id){
    draw_mesh(&chunk->mesh, texture_id);
}

void update_chunk(chunk_t *chunk){

}

void destroy_chunk(chunk_t *chunk){

}