

#include <assert.h>
#include "shader.h"

char* get_shader_content(const char* filename){
    FILE *fp;
    i64 size = 0;
    char* shader_content;

    fp = fopen(filename, "rb");
    assert(fp);

    fseek(fp, 0L, SEEK_END);
    size = ftell(fp) + 1;
    fclose(fp);

    fp = fopen(filename, "r");
    shader_content = memset(malloc(size), '\0', size);
    fread(shader_content, 1, size - 1, fp);
    fclose(fp);

    return shader_content;
}

u32 load_shader(){
    u32 vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
    u32 fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);

#ifdef __arm__
    const char* v_source = get_shader_content("res/vertex_es.glsl");
    const char* f_source = get_shader_content("res/fragment_es.glsl");
#else
    const char* v_source = get_shader_content("res/vertex.glsl");
    const char* f_source = get_shader_content("res/fragment.glsl");
#endif

    i32 result = GL_FALSE;
    int info_log_length;

    printf("Compiling vertex shader...\n");
    glShaderSource(vertex_shader_id, 1, &v_source, NULL);
    glCompileShader(vertex_shader_id);

    glGetShaderiv(vertex_shader_id, GL_COMPILE_STATUS, &result);
    glGetShaderiv(vertex_shader_id, GL_INFO_LOG_LENGTH, &info_log_length);
    if(info_log_length > 0){
        i8* info_log = malloc(sizeof(char) * info_log_length + 1);
        glGetShaderInfoLog(vertex_shader_id, info_log_length, NULL, info_log);
        printf("ERROR: %s\n", info_log);
    }

    printf("Compiling fragmnet shader...\n");
    glShaderSource(fragment_shader_id, 1, &f_source, NULL);
    glCompileShader(fragment_shader_id);

    glGetShaderiv(fragment_shader_id, GL_COMPILE_STATUS, &result);
    glGetShaderiv(fragment_shader_id, GL_INFO_LOG_LENGTH, &info_log_length);
    if(info_log_length > 0){
        i8* info_log = malloc(sizeof(char) * info_log_length + 1);
        glGetShaderInfoLog(fragment_shader_id, info_log_length, NULL, info_log);
        printf("ERROR: %s\n", info_log);
    }

    GLuint program_id = glCreateProgram();
    glAttachShader(program_id, vertex_shader_id);
    glAttachShader(program_id, fragment_shader_id);
    glLinkProgram(program_id);

    glDetachShader(program_id, vertex_shader_id);
    glDetachShader(program_id, fragment_shader_id);

    glDeleteShader(vertex_shader_id);
    glDeleteShader(fragment_shader_id);

    return program_id;
}
