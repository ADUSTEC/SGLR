#version 400 core
layout (location = 0) in vec3 a_pos; // prefix a for attribute
layout (location = 1) in vec3 a_rgb;
layout (location = 2) in vec2 a_uv;
layout (location = 3) in vec3 a_normals;

uniform mat4 u_projection;
uniform mat4 u_view;
uniform mat4 u_model;

out vec3 o_rgb; // prefix o for output
out vec2 o_uv;
out vec3 o_normal;

out mat4 o_projection;
out mat4 o_view;
out mat4 o_model;


void main()
{
   o_rgb = a_rgb;
   o_uv = a_uv;
   o_normal = a_normals;

   o_projection = u_projection;
   o_view = u_view;
   o_model = u_model;

   gl_Position = u_projection * u_view * u_model * vec4(a_pos.x, a_pos.y, a_pos.z, 1.0);
}