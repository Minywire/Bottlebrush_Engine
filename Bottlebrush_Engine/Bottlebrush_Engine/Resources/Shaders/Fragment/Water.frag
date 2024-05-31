#version 330 core

in vec3 vertexColour;
out vec4 fragColour;

void main() {
    fragColour = vec4(vertexColour, 1.0);
}


//varying vec3 position;
//varying vec3 worldNormal;
//varying vec3 eyeNormal;
//uniform vec3 eyePos;
//uniform samplerCube envMap;

//vec3 eye = normalize(eyePos - position);
//vec3 r = reflect(eye, worldNormal);
//vec4 color = textureCube(envMap, r);
//color.a = 0.5;
//gl_FragColor = color;
