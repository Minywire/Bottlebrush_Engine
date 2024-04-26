#version 330 core

struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

in vec2 tex_coord;

out vec4 color;

//uniform Material material;
uniform vec3 lightColour;
uniform sampler2D u_Texture;

void main()
{
	float ambientStrengh = 0.1f;
	vec3 ambient = ambientStrengh * lightColour;
	vec3 result = ambient * vec3(texture(u_Texture, tex_coord));
	color = vec4(result, 1.0f);
//	color = texture(u_Texture, tex_coord);
}
