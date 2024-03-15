#version 400 core

in vec4 clipSpace;
in vec2 textureCoords;
in vec3 toCameraVector;
in vec3 fromLightVector;

out vec4 out_Color;

uniform sampler2D reflectionTex;
uniform sampler2D refractionTex;
uniform sampler2D dudvMap;
uniform sampler2D normalMap;
uniform sampler2D depthMap;
uniform vec3 lightColor;

uniform float moveFactor;
uniform float cameraNearPlane;
uniform float cameraFarPlane;

const float waveStrength = 0.04;
const float shineDamper = 20;
const float reflectivity = 0.6;

void main(void) {
    // Normalized device coords
    vec2 ndc = (clipSpace.xy / clipSpace.w) / 2.0 + 0.5;
    vec2 refractionTexCoords = vec2(ndc.x, ndc.y);
    vec2 reflectionTexCoords = vec2(ndc.x, -ndc.y);

    float depth = texture(depthMap, refractionTexCoords).r;
    float floorDistance = 2.0 * cameraNearPlane * cameraFarPlane / (cameraFarPlane + cameraNearPlane - (2.0 * depth - 1.0) * (cameraFarPlane - cameraNearPlane));
    depth = gl_FragCoord.z;
    float waterDistance = 2.0 * cameraNearPlane * cameraFarPlane / (cameraFarPlane + cameraNearPlane - (2.0 * depth - 1.0) * (cameraFarPlane - cameraNearPlane));
    float waterDepth = floorDistance - waterDistance;

    vec2 distortedTexCoords = texture(dudvMap, vec2(textureCoords.x + moveFactor, textureCoords.y)).rg * 0.1;
    distortedTexCoords = textureCoords + vec2(distortedTexCoords.x, distortedTexCoords.y + moveFactor);
    vec2 totalDistortion = (texture(dudvMap, distortedTexCoords).rg * 2.0 - 1.0) * waveStrength * clamp(waterDepth / 20.0, 0.0, 1.0);
                                                                                                // fixes the glitch effect at edges

    reflectionTexCoords += totalDistortion;
    reflectionTexCoords.x = clamp(reflectionTexCoords.x, 0.01, 0.99); // Fixes the glitches in the corners of the screen
    reflectionTexCoords.y = clamp(reflectionTexCoords.y, -0.99, -0.01); // because Y is flipped

    refractionTexCoords += totalDistortion;
    refractionTexCoords = clamp(refractionTexCoords, 0.01, 0.99);

    vec4 reflectionCol = texture(reflectionTex, reflectionTexCoords);
    vec4 refractionCol = texture(refractionTex, refractionTexCoords);

    vec3 viewVector = normalize(toCameraVector);
    float refractiveFactor = dot(viewVector, vec3(0, 1, 0));
    refractiveFactor = pow(refractiveFactor, 0.5);

    vec4 normalMapColor = texture(normalMap, distortedTexCoords);
    vec3 normal = vec3(normalMapColor.r * 2.0 - 1.0, normalMapColor.b, normalMapColor.g * 2.0 - 1.0);
    normal = normalize(normal);

    vec3 reflectedLight = reflect(normalize(fromLightVector), normal);
    float specular = max(dot(reflectedLight, viewVector), 0.0);
    specular = pow(specular, shineDamper);
    vec3 specularHighlights = lightColor * specular * reflectivity * (1 - refractiveFactor);

    reflectionCol += vec4(specularHighlights, 0.0);
    out_Color = mix(reflectionCol, refractionCol, refractiveFactor);
    out_Color = mix(out_Color, vec4(0, 0.2, 0.7, 1.0), 0.3);
    out_Color.a = clamp(waterDepth / 5.0, 0.0, 1.0);
}
