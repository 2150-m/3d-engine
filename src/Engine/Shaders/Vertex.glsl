#version 400 core

const int MAX_LIGHTS = 20;

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texture;
layout(location = 2) in vec3 normal;

out vec2 textureCoords;
out vec3 surfaceNormal;
out vec3 toLightVec[MAX_LIGHTS];
out vec3 toCameraVec;

uniform mat4 transformMat;
uniform mat4 projectionMat;
uniform mat4 viewMat;
uniform vec3 lightPosition[MAX_LIGHTS];

uniform float useFakeLighting;

uniform vec4 plane;

void main(void) {
	vec4 worldPosition = transformMat * vec4(position, 1.0);

	gl_ClipDistance[0] = dot(worldPosition, plane); // Distance from the plane

	gl_Position = projectionMat * viewMat * worldPosition;
	textureCoords = texture;

	vec3 actualNormal = normal;
	if (useFakeLighting > 0.5) {
		actualNormal = vec3(0.0, 1.0, 0.0);
	}

	surfaceNormal = (transformMat * vec4(actualNormal, 0.0)).xyz;

	for (int i = 0; i < MAX_LIGHTS; i++) {
		toLightVec[i] = lightPosition[i] - worldPosition.xyz;
	}
	// viewMatrix contains the negative version of the camera's position
	toCameraVec = (inverse(viewMat) * vec4(0.0, 0.0, 0.0, 1.0)).xyz - worldPosition.xyz;
}
