#include "Engine/Shaders/StaticShader.hpp"
#include "Engine/ECS/Components/LightComponent.hpp"
#include "Engine/Globals.hpp"
#include "Engine/Shaders/ShaderProgram.hpp"
#include "Engine/Other/Math.hpp"
#include <string>

namespace MyEngine {
    using namespace Shaders;

    const std::string StaticShader::VERTEX_SOURCE = "src/Engine/Shaders/Vertex.glsl";
    const std::string StaticShader::FRAGMENT_SOURCE = "src/Engine/Shaders/Fragment.glsl";

    StaticShader::StaticShader() : ShaderProgram(VERTEX_SOURCE.c_str(), FRAGMENT_SOURCE.c_str()) {
        BindAttributes();
        GetAllUniformLocations();
    }

    void StaticShader::BindAttributes() {
        BindAttribute(0, "position");
        BindAttribute(1, "texture");
        BindAttribute(2, "normal");
    }

    void StaticShader::GetAllUniformLocations() {
        location_transformMat = GetUniformLocation("transformMat");
        location_projectionMat = GetUniformLocation("projectionMat");
        location_viewMat = GetUniformLocation("viewMat");
        location_shineDamper = GetUniformLocation("shineDamper");
        location_reflectivity = GetUniformLocation("reflectivity");
        location_useFakeLighting = GetUniformLocation("useFakeLighting");
        location_isColliding = GetUniformLocation("isColliding");
        location_plane = GetUniformLocation("plane");

        for (int i = 0; i < MAX_LIGHTS; i++) {
            std::string str = "lightPosition[" + std::to_string(i) + "]";
            location_lightPosition[i] = GetUniformLocation(&str[0]);
            str = "lightColor[" + std::to_string(i) + "]";
            location_lightColor[i] = GetUniformLocation(&str[0]);
            str = "attenuation[" + std::to_string(i) + "]";
            location_attenuation[i] = GetUniformLocation(&str[0]);
        }
    }

    void StaticShader::LoadPlane(const glm::vec4& vec) {
        LoadVector(location_plane, vec);
    }

    void StaticShader::LoadIsColliding(bool value) {
        LoadBool(location_isColliding, value);
    }

    void StaticShader::LoadUseFakeLighting(bool value) {
        LoadBool(location_useFakeLighting, value);
    }

    void StaticShader::LoadShineVariables(float damper, float reflectivity) {
        LoadFloat(location_shineDamper, damper);
        LoadFloat(location_reflectivity, reflectivity);
    }

    void StaticShader::LoadTransformMat(const glm::mat4& matrix) {
        LoadMatrix(location_transformMat, matrix);
    }

    void StaticShader::LoadProjectionMat(const glm::mat4 &matrix) {
        LoadMatrix(location_projectionMat, matrix);
    }

    void StaticShader::LoadViewMat(const Entities::Camera& camera) {
        LoadMatrix(location_viewMat, Other::Maths::CreateViewMatrix(camera));
    }

    void StaticShader::LoadLights(const std::vector<Components::LightComponent>& lights) {
        for (int i = 0; i < MAX_LIGHTS; i++) {
            if (i < (int)lights.size()) {
                LoadVector(location_lightPosition[i], Globals::entityMap.at(lights[i].GetEntityID()).GetPosition());
                LoadVector(location_lightColor[i], lights[i].GetColor());
                LoadVector(location_attenuation[i], lights[i].GetAttenuation());
            } else {
                LoadVector(location_lightPosition[i], glm::vec3(0, 0, 0));
                LoadVector(location_lightColor[i], glm::vec3(0,0,0));
                LoadVector(location_attenuation[i], glm::vec3(1, 0, 0));
            }
        }
    }
}
