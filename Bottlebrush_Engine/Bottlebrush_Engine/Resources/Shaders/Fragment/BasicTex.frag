#version 330 core

struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

in vec2 tex_coord;
in vec3 normal;
in vec3 fragPos;

out vec4 color;

//uniform Material material;
uniform vec3 lightColour;
uniform sampler2D u_Texture;
uniform vec3 lightPos;

void main()
{
	// Ambient
	float ambientStrengh = 0.9f;
	vec3 ambient = ambientStrengh * lightColour;

	// Diffuse
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(lightPos - fragPos);
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = diff * lightColour;

	vec3 result = (ambient * diffuse) * vec3(texture(u_Texture, tex_coord));
	color = vec4(result, 1.0f);
}
