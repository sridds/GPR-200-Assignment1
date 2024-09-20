#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// texture samplers
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	vec4 texColor = texture(texture1, TexCoord);
    if(texColor.a < 0.1)
        texColor = texture(texture2, TexCoord);

	FragColor = mix(texColor, texture(texture2, TexCoord), 0.7);
}