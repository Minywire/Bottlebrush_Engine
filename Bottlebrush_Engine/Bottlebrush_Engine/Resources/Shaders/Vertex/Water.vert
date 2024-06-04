#version 330 core
//const float pi = 3.1459;

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNorm;
layout(location = 2) in vec2 aTex;

out vec2 tex_coord;
out vec3 normal;
out vec3 fragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = projection * view * model * vec4(aPos, 1.0f);
    fragPos = vec3(model * vec4(aPos, 1.0));

    tex_coord = aTex * 100;
    normal = mat3(transpose(inverse(model))) * aNorm;

    gl_Position = projection * view * vec4(fragPos, 1.0f);
}
