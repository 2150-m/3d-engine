#ifndef STATICSHADER_H
#define STATICSHADER_H

#include "Engine/Shaders/ShaderProgram.hpp"
#include "Engine/ECS/Entities/Camera.hpp"
#include "Engine/ECS/Entities/Light.hpp"
#include "Engine/ECS/Components/LightComponent.hpp"
#include <array>
#include <string>

namespace MyEngine {
    namespace Shaders {
        class StaticShader : public ShaderProgram {
        private:
            static const int MAX_LIGHTS = 20;
            static const std::string VERTEX_SOURCE;
            static const std::string FRAGMENT_SOURCE;

            GLint location_transformMat,
                location_projectionMat,
                location_viewMat,
                location_shineDamper,
                location_reflectivity,
                location_useFakeLighting,
                location_isColliding,
                location_plane;

            GLint location_lightPosition[MAX_LIGHTS],
                location_lightColor[MAX_LIGHTS],
                location_attenuation[MAX_LIGHTS];

        protected:
            void BindAttributes();

            void GetAllUniformLocations();

        public:
            StaticShader();

            void LoadTransformMat(const glm::mat4& matrix);
            void LoadProjectionMat(const glm::mat4& matrix);
            void LoadViewMat(const Entities::Camera&);
            void LoadLights(const std::vector<Components::LightComponent>& lights);
            void LoadShineVariables(float, float);
            void LoadUseFakeLighting(bool);
            void LoadIsColliding(bool);
            void LoadPlane(const glm::vec4&);
        };
    }
}

#endif
