#version 330 core

uniform bool gGrayscale;
uniform sampler2D gTexHeight0;
uniform sampler2D gTexHeight1;
uniform sampler2D gTexHeight2;
uniform sampler2D gTexHeight3;
uniform float gHeight0;
uniform float gHeight1;
uniform float gHeight2;
uniform float gHeight3;
uniform vec3 gReversedLightDir;

layout (location = 0) out vec4 FragCol;

in vec4 TexCol;
in vec2 Tex;
in vec3 WorldPos;
in vec3 Normal;

vec4 CalcTexColor() {
    vec4 TexCol;
    float Height = WorldPos.y;

    if (Height < gHeight0) {
        TexCol = texture(gTexHeight0, Tex);
    } else if (Height < gHeight1) {
        vec4 Col0 = texture(gTexHeight0, Tex);
        vec4 Col1 = texture(gTexHeight1, Tex);
        float Delta = gHeight1 - gHeight0;
        float Ratio = (Height - gHeight0) / Delta;
        TexCol = mix(Col0, Col1, Ratio);
    } else if (Height < gHeight2) {
        vec4 Col0 = texture(gTexHeight1, Tex);
        vec4 Col1 = texture(gTexHeight2, Tex);
        float Delta = gHeight2 - gHeight1;
        float Ratio = (Height - gHeight1) / Delta;
        TexCol = mix(Col0, Col1, Ratio);
    } else if (Height < gHeight3) {
        vec4 Col0 = texture(gTexHeight2, Tex);
        vec4 Col1 = texture(gTexHeight3, Tex);
        float Delta = gHeight3 - gHeight2;
        float Ratio = (Height - gHeight2) / Delta;
        TexCol = mix(Col0, Col1, Ratio);
    } else {
        TexCol = texture(gTexHeight3, Tex);
    }

    return TexCol;
}

void main() {
    vec4 Colour = CalcTexColor();
    vec3 Normal = normalize(Normal);
    float Diffuse = dot(Normal, gReversedLightDir);
    Diffuse = max(0.3, Diffuse);

    if (gGrayscale) FragCol = TexCol;
    else FragCol = TexCol * Colour * Diffuse;
}
