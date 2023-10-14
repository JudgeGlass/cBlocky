#version 310 es

out mediump vec4 out_color;

in mediump vec2 TexCoord;
in mediump float light_level;

uniform sampler2D blockTexture;

void main(){
    mediump vec4 color = texture(blockTexture, TexCoord);

    //color.x *= light_level;
    //color.y *= light_level;
    //color.z *= light_level;

    out_color = color;
    if(out_color.a == 0.0) discard;
}