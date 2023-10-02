

#ifndef CBLOCKY_SHADER_H
#define CBLOCKY_SHADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <GL/glew.h>

static char* get_shader_content(const char* filename);

void load_shader(GLuint* _program_id);

#endif //CBLOCKY_SHADER_H
