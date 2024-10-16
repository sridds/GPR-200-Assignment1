#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform float time;

// texture samplers
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	vec2 vCoord = vec2(TexCoord.x, TexCoord.y - sin(time + TexCoord.x / 2.0f));

	vec4 texColor = texture(texture1, vCoord);
    if(texColor.a < 0.1)
        texColor = texture(texture2, vCoord);

	FragColor = mix(texColor, texture(texture2, vCoord), 0.7);
}