#version 330 core

layout (location = 0) in vec3 pos;

out float height;
out vec3 position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    height = pos.y;
    position = (view * model * vec4(pos, 1.0f)).xyz;
    gl_Position = projection * view * model * vec4(pos, 1.0f);
}
