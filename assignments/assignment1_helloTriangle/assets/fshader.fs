#version 330 core
out vec4 FragColor;
in vec3 ourColor;
uniform float value;

void main()
{
   FragColor = vec4(ourColor * value, 1.0);
};