#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

uniform float time;

out vec3 ourColor;
out vec2 TexCoord;

void main()
{
	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 0.3f);
	ourColor = aColor;
	TexCoord = vec2((aTexCoord.x * 7) + time, (aTexCoord.y * 7));
}