#version 400 core

const int MAX_LIGHTS = 20;
const float levels = 3.0;

in vec2 textureCoords;
in vec3 surfaceNormal;
in vec3 toLightVec[MAX_LIGHTS];
in vec3 toCameraVec;

layout(location = 0) out vec4 out_Color;

uniform sampler2D textureSampler;
uniform vec3 lightColor[MAX_LIGHTS];
uniform vec3 attenuation[MAX_LIGHTS];
uniform float shineDamper;
uniform float reflectivity;
uniform float isColliding;

void main(void) {
    vec3 unitNormal = normalize(surfaceNormal);
    vec3 unitToCameraVec = normalize(toCameraVec);

    vec3 totalDiffuse = vec3(0.0);
    vec3 totalSpecular = vec3(0.0);

    for (int i = 0; i < MAX_LIGHTS; i++) {
        float distanceToLight = length(toLightVec[i]);
        float attenuationFactor = attenuation[i].x + (attenuation[i].y * distanceToLight) + (attenuation[i].z * distanceToLight * distanceToLight);

        vec3 unitLightVec = normalize(toLightVec[i]);
        float nDot1 = dot(unitNormal, unitLightVec);

        float brightness = max(nDot1, 0.0);
        float level = floor(brightness * levels);
        brightness = level / levels;

        vec3 lightDir = -unitLightVec;
        vec3 reflectedDir = reflect(lightDir, unitNormal);

        float specularFactor = dot(reflectedDir, unitToCameraVec);
        specularFactor = max(specularFactor, 0.0); // brightness can't be negative

        float dampedFactor = pow(specularFactor, shineDamper); // makes low specular factors even lower
        level = floor(dampedFactor * levels);
        dampedFactor = level / levels;

        vec3 finalSpecular = (dampedFactor * reflectivity * lightColor[i]) / attenuationFactor;
        vec3 diffuse = (brightness * lightColor[i]) / attenuationFactor;

        totalDiffuse = totalDiffuse + diffuse;
        totalSpecular = totalSpecular + finalSpecular;
    }

    totalDiffuse = max(totalDiffuse, 0.2);

    vec4 textureColor = texture(textureSampler, textureCoords);
    if (textureColor.a < 0.5) { discard; }

    if (isColliding == 1.0) { textureColor += vec4(0.6, 0.6, 0.6, 2); }
    out_Color = vec4(totalDiffuse, 1.0) * textureColor + vec4(totalSpecular, 1.0);
}
