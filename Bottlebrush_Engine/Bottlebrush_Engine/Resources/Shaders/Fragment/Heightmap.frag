#version 330 core

out vec4 frag_col;

in float height;

void main() {
    float shift = (height + 16.0f) / 32.0f;
    frag_col = vec4(shift, shift, shift, 1.0f);
}
