#version 430 core

out vec4 o_fragout;

in DATA 
{
	vec4 color;
	vec2 uv;
	float ts;
} i_data;

uniform sampler2D u_tex[32];

void main()
{	
	int ind = int(i_data.ts);
    o_fragout = texture(u_tex[ind], i_data.uv) * i_data.color;
}