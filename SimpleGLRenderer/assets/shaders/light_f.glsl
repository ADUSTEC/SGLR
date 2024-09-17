#version 420 core

out vec4 o_fragout;

uniform vec4 u_lightcolor;

void main()
{
	o_fragout = u_lightcolor;
}