#version 330 core
out vec4 FragColor;
in vec3 Normal;
in vec2 TexCoord;
in vec3 FragPos;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 viewPos; 

void main()
{
	vec4 texColor = texture(texture1, TexCoord);
	if(texColor.a < 0.1)
		texColor = texture(texture2, TexCoord);

	// ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

	// diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	// specular
    float specularStrength = 1.0;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;  

	// get final result
	vec4 m = mix(texColor, texture(texture2, TexCoord), 0.7);
	vec3 result = (ambient + diffuse + specular) * vec3(m.x, m.y, m.z);
	FragColor = vec4(result, 1.0f);
};