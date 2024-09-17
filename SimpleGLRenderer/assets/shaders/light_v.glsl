#version 420 core

layout (location = 0) in vec3 a_pos;

uniform mat4 u_projection;
uniform mat4 u_view;
uniform mat4 u_model;

void main()
{
    o_projection = u_projection;
    o_view = u_view;
    o_model = u_model;

	gl_Position = u_projection * u_view * u_model * vec4(a_pos.x, a_pos.y, a_pos.z, 1.0);
}