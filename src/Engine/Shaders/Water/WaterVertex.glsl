#version 400 core

in vec2 position;

out vec4 clipSpace;
out vec2 textureCoords;
out vec3 toCameraVector;
out vec3 fromLightVector;

uniform mat4 projectionMat;
uniform mat4 modelMat;
uniform mat4 viewMat;
uniform vec3 cameraPosition;
uniform vec3 lightPosition;

const float tiling = 4.0;

void main(void) {
    vec4 worldPosition = modelMat * vec4(position.x, 0.0, position.y, 1.0);
    clipSpace = projectionMat * viewMat * worldPosition;
    gl_Position = clipSpace;
    textureCoords = vec2(position.xy / 2.0 + 0.5) * tiling;
    toCameraVector = cameraPosition - worldPosition.xyz;
    fromLightVector = worldPosition.xyz - lightPosition;
}
