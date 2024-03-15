#include "Engine/Shaders/Skybox/SkyboxRenderer.hpp"
#include "Engine/Rendering/Loader.hpp"
#include "Engine/Shaders/Skybox/SkyboxShader.hpp"
#include <GL/gl.h>

namespace MyEngine {
    using namespace Skybox;

    const float SkyboxRenderer::m_SIZE = 500;

    const std::vector<float> SkyboxRenderer::m_VERTICES = {
        -m_SIZE,  m_SIZE, -m_SIZE,
        -m_SIZE, -m_SIZE, -m_SIZE,
        m_SIZE, -m_SIZE, -m_SIZE,
        m_SIZE, -m_SIZE, -m_SIZE,
        m_SIZE,  m_SIZE, -m_SIZE,
        -m_SIZE,  m_SIZE, -m_SIZE,

        -m_SIZE, -m_SIZE,  m_SIZE,
        -m_SIZE, -m_SIZE, -m_SIZE,
        -m_SIZE,  m_SIZE, -m_SIZE,
        -m_SIZE,  m_SIZE, -m_SIZE,
        -m_SIZE,  m_SIZE,  m_SIZE,
        -m_SIZE, -m_SIZE,  m_SIZE,

        m_SIZE, -m_SIZE, -m_SIZE,
        m_SIZE, -m_SIZE,  m_SIZE,
        m_SIZE,  m_SIZE,  m_SIZE,
        m_SIZE,  m_SIZE,  m_SIZE,
        m_SIZE,  m_SIZE, -m_SIZE,
        m_SIZE, -m_SIZE, -m_SIZE,

        -m_SIZE, -m_SIZE,  m_SIZE,
        -m_SIZE,  m_SIZE,  m_SIZE,
        m_SIZE,  m_SIZE,  m_SIZE,
        m_SIZE,  m_SIZE,  m_SIZE,
        m_SIZE, -m_SIZE,  m_SIZE,
        -m_SIZE, -m_SIZE,  m_SIZE,

        -m_SIZE,  m_SIZE, -m_SIZE,
        m_SIZE,  m_SIZE, -m_SIZE,
        m_SIZE,  m_SIZE,  m_SIZE,
        m_SIZE,  m_SIZE,  m_SIZE,
        -m_SIZE,  m_SIZE,  m_SIZE,
        -m_SIZE,  m_SIZE, -m_SIZE,

        -m_SIZE, -m_SIZE, -m_SIZE,
        -m_SIZE, -m_SIZE,  m_SIZE,
        m_SIZE, -m_SIZE, -m_SIZE,
        m_SIZE, -m_SIZE, -m_SIZE,
        -m_SIZE, -m_SIZE,  m_SIZE,
        m_SIZE, -m_SIZE,  m_SIZE
    };

    const std::vector<std::string> SkyboxRenderer::m_TEXTURE_FILES = {
        "right.png", "left.png", "top.png", "bottom.png", "back.png", "front.png"
    };

    SkyboxRenderer::SkyboxRenderer(const glm::mat4& projectionMatrix) :
            m_cube(Rendering::Loader::LoadToVAO(m_VERTICES, 3)),
            m_textureID(Rendering::Loader::LoadCubeMap(m_TEXTURE_FILES)),
            m_shader(SkyboxShader())
    {
        m_shader.Start();
        m_shader.LoadProjectionMat(projectionMatrix);
        m_shader.Stop();
    }

    void SkyboxRenderer::Render(const Entities::Camera& camera) {
        glDepthMask(GL_FALSE);

        m_shader.Start();
        m_shader.LoadViewMat(camera);

        glBindVertexArray(m_cube.GetID());
        glEnableVertexAttribArray(0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureID);
        glDrawArrays(GL_TRIANGLES, 0, m_cube.GetVertexCount());
        glDisableVertexAttribArray(0);
        glBindVertexArray(0);

        m_shader.Stop();

        glDepthMask(GL_TRUE);
    }
}
