#ifndef WATERRENDERER_H
#define WATERRENDERER_H

#include "Engine/ECS/Components/LightComponent.hpp"
#include "Engine/Shaders/Water/WaterFrameBuffer.hpp"
#include "Engine/Shaders/Water/WaterShader.hpp"
#include "Engine/Other/Math.hpp"
#include "Engine/ECS/Entities/Camera.hpp"
#include "Engine/Rendering/Loader.hpp"
#include "Engine/Models/RawModel.hpp"
#include "Engine/Shaders/Water/WaterTile.hpp"
#include <GL/gl.h>
#include <string>
#include <vector>

namespace MyEngine {
    namespace Water {
        class WaterRenderer {
        public:
            WaterRenderer(WaterShader shader, const glm::mat4& projectionMatrix, const WaterFrameBuffer& fbos);

            void Render(const std::vector<WaterTile>& water, const Entities::Camera& camera, const Components::LightComponent& light);

        private:
            void PrepareRender(const Entities::Camera& camera, const Components::LightComponent& light);

            void Unbind();

            Models::RawModel SetUpVAO();

            // VARS
            static const std::string DUDV_MAP;
            static const std::string NORMAL_MAP;

            WaterShader m_shader;
            Models::RawModel m_model;
            WaterFrameBuffer m_fbos;

            int m_dudvTexture;
            int m_normalMap;
            float m_moveFactor;
        };
    }
}

#endif
