#version 430 core

layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec4 a_col;

uniform mat4 ortho;

out DATA
{
    vec4 color;
} o_data;

void main()
{
    o_data.color = a_col;
    gl_Position = ortho * vec4( a_pos, 1.0);
}