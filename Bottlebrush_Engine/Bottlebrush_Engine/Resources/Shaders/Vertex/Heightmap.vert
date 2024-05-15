#version 330 core

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float min_height;
uniform float max_height;

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv_coord;

out vec4 tex_color;
out vec2 tex_coord;

void main() {
    gl_Position = projection * view * model * vec4(position, 1.0);

    float delta = max_height - min_height;
    float ratio = (position.y - min_height) / delta;
    float shift = ratio * 0.8 + 0.2;

    tex_color = vec4(shift, shift, shift, 1.0);
    tex_coord = uv_coord;
}
