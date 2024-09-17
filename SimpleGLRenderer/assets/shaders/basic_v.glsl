#version 420 core

layout (location = 0) in vec3 a_pos; // prefix a for attribute
layout (location = 1) in vec3 a_rgb;
layout (location = 2) in vec2 a_uv;
layout (location = 3) in vec3 a_normals;

uniform mat4 u_projection;
uniform mat4 u_view;
uniform mat4 u_model;

out DATA
{
   vec3 rgb;
   vec2 uv;
   vec3 normal;

   mat4 projection;
   mat4 view;
   mat4 model;

   vec3 cpos;

} o_data;


void main()
{
   o_data.rgb = a_rgb;
   o_data.uv = a_uv;
   o_data.normal = a_normals;

   o_data.projection = u_projection;
   o_data.view = u_view;
   o_data.model = u_model;

   o_data.cpos = vec3(u_model * vec4(a_pos, 1.0f));

   gl_Position = u_projection * u_view * vec4(o_data.cpos, 1.0f);
}