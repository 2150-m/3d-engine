#include "Engine/Rendering/MasterRenderer.hpp"
#include "Engine/ECS/Components/LightComponent.hpp"
#include "Engine/Other/Settings.hpp"
#include "Engine/Globals.hpp"

#include <GL/glext.h>
#include <vector>
#include <iostream>

namespace MyEngine {
    using namespace Rendering;

    glm::mat4 MasterRenderer::m_projectionMatrix = MasterRenderer::CreateProjectionMatrix();

    MasterRenderer::MasterRenderer() :
            m_entityRenderer(m_shader, m_projectionMatrix),
            m_skyboxRenderer(m_projectionMatrix)
    {
        MasterRenderer::EnableCulling();
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
    }

    void MasterRenderer::Prepare() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.32, 0.6, 0.95, 1);
    }

    void MasterRenderer::RenderScene(std::vector<Components::LightComponent>& lights, const Entities::Camera& camera, const glm::vec4& clipPlane) {
        for (auto& p : Globals::entityMap) { ProcessEntity(&p.second); }

        Render(lights, camera, clipPlane);
    }

    void MasterRenderer::Render(std::vector<Components::LightComponent>& lights, const Entities::Camera& camera, const glm::vec4& clipPlane) {
        MasterRenderer::Prepare();
        m_shader.Start();
        if (!lights.empty())
            m_shader.LoadLights(lights);
        m_shader.LoadViewMat(camera);
        m_shader.LoadPlane(clipPlane);

        m_entityRenderer.Render(m_entityBatches);

        m_shader.Stop();

        m_skyboxRenderer.Render(camera);

        m_entityBatches.clear();
    }

    void MasterRenderer::ProcessEntity(const Entities::Entity* entity) {
        const Models::TexturedModel* model = &entity->GetModel();

        if (m_entityBatches.count(model)) {
            m_entityBatches[model].push_back(entity);
        } else {
            std::vector<const Entities::Entity*> newBatch;
            newBatch.push_back(entity);
            m_entityBatches[model] = newBatch;
        }
    }

    void MasterRenderer::CleanUp() {
        m_shader.CleanUp();
    }

    void MasterRenderer::EnableCulling() {
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
    }

    void MasterRenderer::DisableCulling() {
        glDisable(GL_CULL_FACE);
    }

    glm::mat4 MasterRenderer::CreateProjectionMatrix() {
        return glm::perspective(glm::radians(Settings::fov), (float)Settings::windowWidth / (float)Settings::windowHeight, Settings::nearPlane, Settings::farPlane);
    }
}
