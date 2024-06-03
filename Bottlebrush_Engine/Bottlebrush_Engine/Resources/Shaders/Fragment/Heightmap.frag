#version 330 core

uniform bool gGrayscale;
uniform sampler2D gTex;
uniform vec3 gReversedLightDir;

layout (location = 0) out vec4 FragCol;

in vec4 TexCol;
in vec2 Tex;
in vec3 WorldPos;
in vec3 Normal;

void main() {
    vec4 Colour = texture(gTex, Tex);
    vec3 Normal = normalize(Normal);
    float Diffuse = max(0.0, dot(Normal, gReversedLightDir));
    Diffuse = max(0.3, Diffuse);

    if (gGrayscale) FragCol = TexCol;
    else FragCol = TexCol * Colour * Diffuse;
}
