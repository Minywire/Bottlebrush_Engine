#version 330 core

// in vec2 tex_coord;

out vec4 color;

uniform sampler2D u_Texture;
uniform vec4 u_Color;
void main()
{
//	color = texture(u_Texture, tex_coord);
	color = u_Color;
}
