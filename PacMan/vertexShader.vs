#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in  vec2 texCoord;

uniform mat4 pvm;
out vec2 Tex;

void main()
{
    gl_Position = pvm * vec4(aPos.x,aPos.y,aPos.z, 1.0);
	Tex = texCoord;
}