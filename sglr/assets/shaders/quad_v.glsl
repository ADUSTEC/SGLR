#version 430 core

layout (location = 0) in vec3  a_pos;
layout (location = 1) in vec4  a_col;
layout (location = 2) in vec2  a_uv;
layout (location = 3) in float a_ts;

uniform mat4 ortho;

out DATA
{
    vec4 color;
    vec2 uv;
	float ts;
} o_data;

void main()
{
    o_data.color = a_col;
	o_data.uv = a_uv;
	o_data.ts = a_ts;
    gl_Position = ortho * vec4( a_pos, 1.0);
}