#version 330 core

uniform bool grayscale;
uniform sampler2D detail;

layout(location = 0) out vec4 frag_color;

in vec4 tex_color;
in vec2 tex_coord;

void main() {
    vec4 detail_color = texture(detail, tex_coord);

    if (grayscale) frag_color = tex_color;
    else frag_color = tex_color * detail_color;
}
