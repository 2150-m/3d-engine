#ifndef WATERSHADER_H
#define WATERSHADER_H

#include "Engine/ECS/Components/LightComponent.hpp"
#include "Engine/Shaders/ShaderProgram.hpp"
#include "Engine/ECS/Entities/Camera.hpp"
#include "Engine/ECS/Entities/Light.hpp"

namespace MyEngine {
    namespace Water {
        class WaterShader : public Shaders::ShaderProgram {
        public:
            WaterShader();

            void LoadProjectionMat(const glm::mat4& matrix);
            void LoadViewMat(const Entities::Camera&);
            void LoadModelMat(const glm::mat4& matrix);
            void ConnectTextureUnits();
            void LoadMoveFactor(float factor);
            void LoadLight(const Components::LightComponent& light);

        protected:
            void BindAttributes();

            void GetAllUniformLocations();

        private:
            static const std::string VERTEX_SOURCE;
            static const std::string FRAGMENT_SOURCE;

            GLint location_viewMat = 0;
            GLint location_projectionMat = 0;
            GLint location_modelMat = 0;
            GLint location_refractionTex;
            GLint location_reflectionTex;
            GLint location_dudvMap;
            GLint location_moveFactor;
            GLint location_cameraPosition;
            GLint location_normalMap;
            GLint location_lightColor;
            GLint location_lightPosition;
            GLint location_depthMap;
            GLint location_cameraNearPlane;
            GLint location_cameraFarPlane;
        };
    }
}

#endif
