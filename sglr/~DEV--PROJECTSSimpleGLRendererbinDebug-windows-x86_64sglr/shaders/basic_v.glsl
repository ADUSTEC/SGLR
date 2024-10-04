#version 430 core

layout (location = 0) in vec3 a_pos; // prefix a for attribute
layout (location = 1) in vec3 a_rgb;
layout (location = 2) in vec2 a_uv;
layout (location = 3) in vec3 a_normals;

uniform mat4 u_projection;
uniform mat4 u_view;
uniform mat4 u_model;

out DATA
{
	vec3 pos;
	vec3 rgb;
	vec2 uv;
	vec3 normal;

	mat4 projection;
	mat4 view;
	mat4 model;

	vec3 fpos;

} o_data; 

void main()
{
   o_data.pos = a_pos;
   o_data.rgb = a_rgb;
   o_data.uv = a_uv;
   o_data.normal = a_normals;

   o_data.projection = u_projection;
   o_data.view = u_view;
   o_data.model = u_model;

   o_data.fpos = vec3(vec4(a_pos, 1.0f) * u_model);

   gl_Position = u_projection * u_view * vec4(o_data.fpos, 1.0f);
}