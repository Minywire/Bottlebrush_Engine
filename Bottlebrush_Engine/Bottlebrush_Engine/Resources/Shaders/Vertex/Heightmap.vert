#version 330 core

uniform mat4 gModel;
uniform mat4 gView;
uniform mat4 gProjection;
uniform float gMinHeight;
uniform float gMaxHeight;

layout (location = 0) in vec3 InPos;
layout (location = 1) in vec3 InNormal;
layout (location = 2) in vec2 InTex;

out vec4 TexCol;
out vec2 Tex;
out vec3 WorldPos;
out vec3 Normal;

void main() {
    gl_Position = gProjection * gView * gModel * vec4(InPos, 1.0);

    float Delta = gMaxHeight - gMinHeight;
    float Ratio = (InPos.y - gMinHeight) / Delta;
    float Shift = Ratio * 0.8 + 0.2;

    TexCol = vec4(Shift, Shift, Shift, 1.0);
    Tex = InTex;
    WorldPos = InPos;
    Normal = InNormal;
}
