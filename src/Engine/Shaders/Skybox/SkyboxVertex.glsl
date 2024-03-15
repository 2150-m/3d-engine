#version 400 core

in vec3 position;
out vec3 texCoords;

uniform mat4 projectionMat;
uniform mat4 viewMat;

void main(void) {
    gl_Position = projectionMat * viewMat * vec4(position, 1.0);
    texCoords = position;
}
