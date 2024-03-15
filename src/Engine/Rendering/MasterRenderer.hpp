#ifndef MASTERRENDERER_H
#define MASTERRENDERER_H

#include "Engine/ECS/Components/LightComponent.hpp"
#include "Engine/Shaders/StaticShader.hpp"
#include "Engine/Rendering/EntityRenderer.hpp"
#include "Engine/Shaders/Skybox/SkyboxRenderer.hpp"

#include <map>
#include <vector>

namespace MyEngine {
    namespace Rendering {
        class MasterRenderer {
        public:
            MasterRenderer();

            void Prepare();
            void RenderScene(std::vector<Components::LightComponent>& lights, const Entities::Camera& camera, const glm::vec4& clipPlane);
            void Render(std::vector<Components::LightComponent>& lights, const Entities::Camera& camera, const glm::vec4& plane);
            void ProcessEntity(const Entities::Entity* entity);
            void CleanUp();

            static glm::mat4 CreateProjectionMatrix();

            static void EnableCulling();
            static void DisableCulling();

            static const glm::mat4& GetProjectionMatrix() { return m_projectionMatrix; }

        private:
            static glm::mat4 m_projectionMatrix;
            Shaders::StaticShader m_shader;

            EntityRenderer m_entityRenderer;
            Skybox::SkyboxRenderer m_skyboxRenderer;

            std::map<const Models::TexturedModel*, std::vector<const Entities::Entity*>> m_entityBatches;
        };
    }
}

#endif
