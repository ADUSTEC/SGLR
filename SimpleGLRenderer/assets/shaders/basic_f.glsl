#version 400 core
out vec4 FragColor;

in vec3 o_rgb;
in vec2 o_uv;

uniform sampler2D tex0;

void main()
{
	//FragColor = vec4(o_rgb, 1.0);

	FragColor = vec4(texture(tex0, o_uv));
}