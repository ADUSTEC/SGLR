#version 400 core
out vec4 FragColor;

in vec3 o_rgb;
in vec2 o_uv;
in vec3 o_normal;

in mat4 o_model;
in mat4 o_camera;

uniform sampler2D tex0;

void main()
{
	//FragColor = vec4(o_rgb, 1.0);

	vec3 normal = normalize(o_normal);
	//FragColor = vec4(o_rgb+normal.r, 1.0);

	FragColor = vec4(texture(tex0, o_uv).rgb * (((normal.r+0.2) * (normal.g+0.1) * (normal.b+0.4))*14), 1.0);
}