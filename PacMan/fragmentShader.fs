#version 330 core
out vec4 FragColor;

// texture samplers
in vec2 Tex;
uniform sampler2D mtexture;

void main()
{
	FragColor = texture(mtexture,Tex);
}