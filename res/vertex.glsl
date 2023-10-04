#version 330 core


layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 3) in float light_level_in;
layout(location = 2) in vec2 aTexCoord;
 
uniform mat4 MVP;

out vec2 TexCoord;
out float light_level;

void main(){
    vec3 pos = vertexPosition_modelspace;
    //pos.x -= 20.0f;

    gl_Position = vec4(pos, 1.0f);  

    TexCoord = aTexCoord;
    light_level = light_level_in;
}