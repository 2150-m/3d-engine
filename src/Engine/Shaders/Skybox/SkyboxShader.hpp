#ifndef SKYBOXSHADER_H
#define SKYBOXSHADER_H

#include "Engine/Shaders/ShaderProgram.hpp"
#include "Engine/ECS/Entities/Camera.hpp"
#include "Engine/ECS/Entities/Light.hpp"
#include <array>
#include <string>

namespace MyEngine {
    namespace Skybox {
        class SkyboxShader : public Shaders::ShaderProgram {
        private:
            static const std::string VERTEX_SOURCE;
            static const std::string FRAGMENT_SOURCE;

            GLint location_viewMat;
            GLint location_projectionMat;

        protected:
            void BindAttributes();

            void GetAllUniformLocations();

        public:
            SkyboxShader();

            void LoadProjectionMat(const glm::mat4& matrix);
            void LoadViewMat(const Entities::Camera&);
        };
    }
}

#endif
