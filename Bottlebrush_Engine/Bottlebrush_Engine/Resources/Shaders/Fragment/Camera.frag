#version 330 core

out vec4 frag_col;

in vec2 tex_coord;

uniform sampler2D tex_0;
uniform sampler2D tex_1;

void main() {
    frag_col = mix(texture(tex_0, tex_coord), texture(tex_1, tex_coord), 0.5);
}
