#version 330 core
out vec4 FragColor;

// texture samplers
in vec2 Tex;
uniform sampler2D mtexture;

void main()
{
	// linearly interpolate between both textures (80% container, 20% awesomeface)
	FragColor = texture(mtexture,Tex);
}