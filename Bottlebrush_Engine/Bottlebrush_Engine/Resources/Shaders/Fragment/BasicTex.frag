#version 330 core

in vec2 tex_coord;
in vec3 normal;
in vec3 fragPos;

out vec4 color;

struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};


uniform vec3 lightColour;
uniform sampler2D u_Texture;
uniform vec3 lightDir;
uniform vec3 viewPos;

void main()
{
	// Ambient
	float ambientStrengh = 0.1f;
	vec3 ambient = ambientStrengh * lightColour;

	// Diffuse
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(lightDir - fragPos);
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = diff * lightColour;

	// Specular
	float specularStrength = 0.9;
	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32);
	vec3 specular = specularStrength * spec * lightColour;

	vec3 result = (ambient + diffuse + specular) * vec3(texture(u_Texture, tex_coord));
	color = vec4(result, 1.0f);
}
