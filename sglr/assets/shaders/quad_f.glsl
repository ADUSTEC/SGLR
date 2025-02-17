#version 430 core

out vec4 o_fragout;

in DATA 
{
	vec4 color;
} i_data;

void main()
{	
    o_fragout = i_data.color;
}