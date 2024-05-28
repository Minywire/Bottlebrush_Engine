#version 330 core

uniform bool grayscale;
uniform sampler2D detail;

layout(location = 0) out vec4 frag_color;

in vec4 tex_color;
in vec2 tex_coord;

uniform vec3 heightmapLightColour;

void main() {
    // Ambient
    float ambientStrengh = 0.1f;
    vec3 ambient = ambientStrengh * heightmapLightColour;

    vec4 detail_color = texture(detail, tex_coord);

    if (grayscale) frag_color = tex_color;
    else frag_color = tex_color * detail_color;
}
