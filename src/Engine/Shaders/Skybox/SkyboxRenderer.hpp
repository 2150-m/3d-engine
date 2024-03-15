#ifndef SKYBOXREND_H
#define SKYBOXREND_H

#include "Engine/Shaders/Skybox/SkyboxShader.hpp"
#include "Engine/Models/RawModel.hpp"

#include <string>
#include <vector>

namespace MyEngine {
    namespace Skybox {
        class SkyboxRenderer {
        public:
            SkyboxRenderer(const glm::mat4&);

            void Render(const Entities::Camera&);

        private:
            static const float m_SIZE;
            static const std::vector<float> m_VERTICES;
            static const std::vector<std::string> m_TEXTURE_FILES;

            Models::RawModel m_cube;
            int m_textureID;
            Skybox::SkyboxShader m_shader;
        };
    }
}

#endif
