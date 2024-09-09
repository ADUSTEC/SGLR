#version 400 core
layout (location = 0) in vec3 a_pos; // prefix a for attribute
layout (location = 1) in vec3 a_rgb;
layout (location = 2) in vec2 a_uv;

out vec3 o_rgb; // prefix o for output
out vec2 o_uv;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_proj;

void main()
{
   gl_Position = u_proj * u_view * u_model * vec4(a_pos.x, a_pos.y, a_pos.z, 1.0);
   o_rgb = a_rgb;
   o_uv = a_uv;
}