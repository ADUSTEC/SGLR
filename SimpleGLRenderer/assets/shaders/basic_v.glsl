#version 400 core
layout (location = 0) in vec3 l_pos;

void main()
{
   gl_Position = vec4(l_pos.x, l_pos.y, l_pos.z, 1.0);
}