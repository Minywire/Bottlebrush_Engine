#version 330 core

in vec2 tex_coord;
in vec3 normal;
in vec3 fragPos;

out vec4 color;

uniform sampler2D u_Texture;

void main() {
    vec3 tex = vec3(texture(u_Texture, tex_coord));
    color = vec4(tex, 0.3f);
}
