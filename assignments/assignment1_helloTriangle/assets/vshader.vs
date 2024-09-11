#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
uniform float time;
out vec3 ourColor;

void main()
{
   gl_Position = vec4(aPos.x, aPos.y + (sin(time * 2.0f + aPos.x) / 5.0f), aPos.z, 1.0);
   ourColor = aColor;
};