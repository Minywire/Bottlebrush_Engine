#version 330 core

layout (location = 0) in vec3 pos;
out vec3 vertexColour;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = projection * view * model * vec4(pos, 1.0f);
    vertexColour = vec3(0.0, 0.0, 1.0);
}
