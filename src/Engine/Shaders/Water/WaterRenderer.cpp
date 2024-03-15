#include "Engine/Shaders/Water/WaterRenderer.hpp"
#include "Engine/ECS/Components/LightComponent.hpp"
#include "Engine/Shaders/Water/WaterFrameBuffer.hpp"
#include "Engine/Other/Settings.hpp"
#include "Engine/Rendering/DisplayManager.hpp"
#include <GL/gl.h>
#include <cmath>

namespace MyEngine {
    using namespace Water;

    const std::string WaterRenderer::DUDV_MAP = "/other/waterdudv.png";
    const std::string WaterRenderer::NORMAL_MAP = "/other/normalmap.png";

    WaterRenderer::WaterRenderer(Water::WaterShader shader, const glm::mat4& projectionMatrix, const WaterFrameBuffer& fbos) :
            m_shader(shader), m_model(SetUpVAO()), m_fbos(fbos),
            m_dudvTexture(Rendering::Loader::LoadTexture(DUDV_MAP)),
            m_normalMap(Rendering::Loader::LoadTexture(NORMAL_MAP))
    {
        m_shader.Start();
        m_shader.ConnectTextureUnits();
        m_shader.LoadProjectionMat(projectionMatrix);
        m_shader.Stop();
    }

    void WaterRenderer::Render(const std::vector<WaterTile>& water, const Entities::Camera& camera, const Components::LightComponent& light) {
        PrepareRender(camera, light);

        for (WaterTile tile : water) {
            // glm::mat4 modelMatrix = Other::Maths::CreateTransformMatrix(
            //     glm::vec3(tile.GetX(), 0, tile.GetZ()), glm::vec3(0), glm::vec3(Water::TILE_SIZE)
            // );

            m_shader.LoadModelMat(tile.GetTransformMatrix());
            glDrawArrays(GL_TRIANGLES, 0, m_model.GetVertexCount());
        }

        Unbind();
    }

    void WaterRenderer::PrepareRender(const Entities::Camera& camera, const Components::LightComponent& light) {
        m_shader.Start();
        m_shader.LoadViewMat(camera);

        m_moveFactor += Settings::WAVE_SPEED * Rendering::DisplayManager::GetDeltaTime();
        m_moveFactor = std::fmod(m_moveFactor, 1);
        m_shader.LoadMoveFactor(m_moveFactor);

        if (light.GetEntityID() != -1)
            m_shader.LoadLight(light);

        glBindVertexArray(m_model.GetID());
        glEnableVertexAttribArray(0);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_fbos.GetReflectionTexture());
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, m_fbos.GetRefractionTexture());
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, m_dudvTexture);
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, m_normalMap);
        glActiveTexture(GL_TEXTURE4);
        glBindTexture(GL_TEXTURE_2D, m_fbos.GetRefractionDepthTexture());

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void WaterRenderer::Unbind() {
        glDisable(GL_BLEND);
        glDisableVertexAttribArray(0);
        glBindVertexArray(0);
        m_shader.Stop();
    }

    Models::RawModel WaterRenderer::SetUpVAO() {
        std::vector<GLfloat> vertices = {
            -1, -1, -1, 1, 1, -1, 1, -1, -1, 1, 1, 1
        };
        return Rendering::Loader::LoadToVAO(vertices, 2);
    }
}
