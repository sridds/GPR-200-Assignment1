#version 330 core
out vec4 FragColor;
in vec3 ourColor;
in vec2 TexCoord;

uniform float value;
uniform sampler2D texture1;

void main()
{
   FragColor = mix(texture(texture1, TexCoord), vec4(ourColor * value, 1.0), 0.5);
};