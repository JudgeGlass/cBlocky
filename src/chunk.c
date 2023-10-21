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
    
    if(y < 0 || y > CHUNK_HEIGHT){
        return 1;
    }

    //printf("Y: %d\n", y);
    assert(!(y > CHUNK_HEIGHT || y < 0));

    block_t *block = NULL;
    if(x < 0){
        if(cx - 1 >= 0){
            block = get_block(get_chunk(world_chunks, 16, 16, cx - 1, cz), 15, y, z);
        }else{
            return 0;
        }
    }else if(x > CHUNK_WIDTH - 1){
        if(cx + 1 < CHUNK_WIDTH){
            block = get_block(get_chunk(world_chunks, 16, 16, cx + 1, cz), 0, y, z);
        }else{
            return 0;
        }
    }else if(z < 0){
        if(cz - 1 >= 0){
            block = get_block(get_chunk(world_chunks, 16, 16, cx, cz - 1), x, y, 15);
        }else{
            return 0;
        }
    }else if(z > CHUNK_DEPTH - 1){
        if(cz + 1 < CHUNK_DEPTH){
            block = get_block(get_chunk(world_chunks, 16, 16, cx, cz + 1), x, y, 0);
        }else{
            return 0;
        }
    }else{
        block = get_block(chunk, x, y, z);
    }

    if(block == NULL) return 0;

    switch (get_type(block))
    {
    case AIR:
    case GLASS:
    case OAK_LEAVES:
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

void set_block(chunk_t *chunk, u8 x, u8 y, u8 z, u8 type){
    block_t *block = get_block(chunk, x, y, z);
    set_type(block, type);
}

void init_chunk(chunk_t *chunk, i32 cx, i32 cz){
    chunk->cx = cx;
    chunk->cz = cz;

    struct osn_context *ctx;
    open_simplex_noise(77374, &ctx);

    for(i32 x = 0; x < CHUNK_WIDTH; x++){
        for(i32 y = 0; y < CHUNK_HEIGHT; y++){
            for(i32 z = 0; z < CHUNK_DEPTH; z++){                
                f32 xx = (f32)(x + cx);
                f32 zz = (f32)(z + cz);
                f32 n = fabs(open_simplex_noise2(ctx,(float)(x+cx*CHUNK_WIDTH + ((float)rand() / (RAND_MAX))) / 80, (float)(z+cz*CHUNK_DEPTH + ((float)rand() / (RAND_MAX))) / 80) * 12);

                u32 l_start = (u32) n + 120;

                block_t block;
                init_block(x, y, z, STONE, 0, &block);

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

    for(i32 x = 0; x < CHUNK_WIDTH; x++){
        for(i32 y = 0; y < CHUNK_HEIGHT; y++){
            for(i32 z = 0; z < CHUNK_DEPTH; z++){
                if(get_type(get_block(chunk, x, y, z)) != GRASS) continue;
                
                if(rand() % 100 < 5)
                    create_tree(chunk, x, y+1, z);
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

static void create_tree(chunk_t *chunk, i32 x, i32 y, i32 z){
    if(y > CHUNK_HEIGHT - 5 || x < 5 || x > 11 || z < 5 || z > 11) return;
    set_type(get_block(chunk, x, y, z), OAK_LOG);
    set_type(get_block(chunk, x, y + 1, z), OAK_LOG);
    set_type(get_block(chunk, x, y + 2, z), OAK_LOG);
    set_type(get_block(chunk, x, y + 3, z), OAK_LOG);
    for(int xx = -2; xx < 3; xx++){
        for(int zz = -2; zz < 3; zz++){
            if(xx == 0 && zz == 0) continue;
            set_type(get_block(chunk, x + xx, y + 3, z + zz), OAK_LEAVES);
            set_type(get_block(chunk, x + xx, y + 4, z + zz), OAK_LEAVES);
        }
    }

    for(int xx = -1; xx < 2; xx++){
        for(int zz = -1; zz < 2; zz++){
            set_type(get_block(chunk, x + xx, y + 5, z + zz), OAK_LEAVES);
        }
    }
}

void draw_chunk(const chunk_t *chunk, u32 texture_id){
    draw_mesh(&chunk->mesh, texture_id);
}

void update_chunk(chunk_t *chunk){

}

void destroy_chunk(chunk_t *chunk){

}